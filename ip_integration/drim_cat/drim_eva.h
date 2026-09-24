// DRIM4HLS as a self-contained EVA packet source.
//
// The Vitis processor (ip/rv_stream_ip.cpp) looks like a pure producer to Allo:
// one output stream, no inputs, program in a ROM baked into the design.
// DRIM4HLS cannot look like that on its own -- it fetches over a channel, so it
// needs instruction and data memory served to it. This module supplies both and
// exposes ONLY the packet stream, so parse_sc_module sees the same 1-port
// producer shape and the Allo side needs no special case.
//
// It also keeps DRIM4HLS's struct payloads (imem_out_t, dmem_in_t, ...) off the
// Allo boundary entirely: the only type that crosses is sc_uint<XLEN>.
#ifndef __DRIM_EVA__H
#define __DRIM_EVA__H

#include <mc_connections.h>
#include <systemc.h>

#include "drim4hls_datatypes.h"
#include "defines.h"
#include "globals.h"
#include "drim4hls.h"
#include "eva_program.h"

// EVA router packet width, from the chip: data[16]|addr<<16|mode<<20|id<<21|rq<<25.
// The port below spells `ac_int<26, false>` LITERALLY rather than using this
// macro: Allo compares the IP's declared type against the design's as TEXT when
// a channel is shared with a kernel, and it cannot expand macros. Keep the two
// in step by hand.
#define PKT_W 26

SC_MODULE(drim_eva) {
    sc_in_clk   clk;
    sc_in<bool> rst;

    // The only Allo-visible port: EVA router packets, one per store to
    // MMIO_BASE. Everything else below is internal.
    //
    // The type is EVA's Pkt (26 bits: data[16] | addr<<16 | mode<<20 | id<<21 |
    // rq<<25), NOT the processor's 32-bit word. Allo declares the channel from
    // this port, and EVA's rdrv_w kernel expects ac_int<26,false>; a 32-bit port
    // here makes the two ends disagree and Connections::Bind fails. Narrowing
    // is exactly what an adapter module is for, and it is lossless -- eva_pkt()
    // only ever fills the low 26 bits.
    Connections::Out< ac_int<26, false> > CCS_INIT_S1(pkt_out);
    // Lane 1, for a 2xN grid. The CPU picks the lane by STORE ADDRESS
    // (MMIO_BASE -> lane 0, MMIO_BASE+1 -> lane 1), so one processor can carry
    // a different program image per lane -- which is the whole reason a 2x2
    // MMM needs this, since every node holds its own stationary weight.
    Connections::Out< ac_int<26, false> > CCS_INIT_S1(pkt_out_b);

    // The CPU's own interfaces, terminated inside this module.
    Connections::Combinational< imem_out_t > CCS_INIT_S1(imem2de_ch);
    Connections::Combinational< imem_in_t >  CCS_INIT_S1(fe2imem_ch);
    Connections::Combinational< dmem_out_t > CCS_INIT_S1(dmem2wb_ch);
    Connections::Combinational< dmem_in_t >  CCS_INIT_S1(wb2dmem_ch);
    // mmio_in has no producer: the EVA boot program only ever STORES packets.
    // A load from >= MMIO_BASE would block forever here, which is the correct
    // behaviour for a starved channel.
    Connections::Combinational< sc_uint<XLEN> > CCS_INIT_S1(mmio_in_ch);
    // The CPU's raw 32-bit store lands here; pkt_th narrows it to PKT_W.
    Connections::Combinational< sc_uint<XLEN> > CCS_INIT_S1(mmio_out_ch);
    Connections::Combinational< sc_uint<XLEN> > CCS_INIT_S1(mmio_out_b_ch);

    // Scalars the CPU drives but nothing here consumes.
    sc_signal<bool>     CCS_INIT_S1(program_end);
    sc_signal<long int> CCS_INIT_S1(icount), CCS_INIT_S1(j_icount);
    sc_signal<long int> CCS_INIT_S1(b_icount), CCS_INIT_S1(m_icount);
    sc_signal<long int> CCS_INIT_S1(o_icount);

    // Instruction and data memory. Both are preloaded with the SAME image, as
    // top.cpp's loader does: the code is fetched from imem and the packet table
    // is read from dmem, and they sit at the same offsets.
    sc_uint<XLEN> imem[ICACHE_SIZE];
    sc_uint<XLEN> dmem[DCACHE_SIZE];

    drim4hls cpu;

    // Adapted from top.cpp's imemory_th/dmemory_th. Two deliberate changes:
    // the random stall counts are gone -- an IP inside a dataflow region should
    // be deterministic, and rand() would make every run differ -- and so are
    // the debug couts, which printed per access.
    void imemory_th() {
        imem2de_ch.ResetWrite();
        fe2imem_ch.ResetRead();
        wait();
        while (true) {
            imem_in_t rq = fe2imem_ch.Pop();
            imem_out_t rs;
            rs.instr_data = imem[rq.instr_addr >> 2];
            wait();                       // one cycle of memory latency
            imem2de_ch.Push(rs);
            wait();
        }
    }

    void dmemory_th() {
        wb2dmem_ch.ResetRead();
        dmem2wb_ch.ResetWrite();
        wait();
        while (true) {
            dmem_in_t rq = wb2dmem_ch.Pop();
            unsigned addr = rq.data_addr;
            dmem_out_t rs;
            wait();
            if (rq.read_en) {
                rs.data_out = dmem[addr];
                dmem2wb_ch.Push(rs);      // only a READ answers
            } else if (rq.write_en) {
                dmem[addr] = rq.data_in;
            }
            wait();
        }
    }

    // Narrow the processor's 32-bit store to EVA's 26-bit packet.
    void pkt_th() {
        mmio_out_ch.ResetRead();
        pkt_out.Reset();
        wait();
        while (true) {
            sc_uint<XLEN> w = mmio_out_ch.Pop();
            pkt_out.Push((ac_int<PKT_W, false>) w.to_uint());
        }
    }

    void pkt_b_th() {
        mmio_out_b_ch.ResetRead();
        pkt_out_b.Reset();
        wait();
        while (true) {
            sc_uint<XLEN> w = mmio_out_b_ch.Pop();
            pkt_out_b.Push((ac_int<PKT_W, false>) w.to_uint());
        }
    }

    SC_HAS_PROCESS(drim_eva);
    drim_eva(sc_module_name n) : sc_module(n), cpu("cpu") {
        // Preload both memories from the baked-in image, exactly as top.cpp's
        // file loader does. This happens at construction, so the program is in
        // place before the first fetch.
        for (unsigned i = 0; i < ICACHE_SIZE; i++) imem[i] = 0;
        for (unsigned i = 0; i < DCACHE_SIZE; i++) dmem[i] = 0;
        for (unsigned i = 0; i < EVA_PROGRAM_WORDS; i++) {
            imem[i] = EVA_PROGRAM[i];
            dmem[i] = EVA_PROGRAM[i];
        }

        cpu.clk(clk);
        cpu.rst(rst);
        cpu.program_end(program_end);
        cpu.icount(icount);     cpu.j_icount(j_icount);
        cpu.b_icount(b_icount); cpu.m_icount(m_icount);
        cpu.o_icount(o_icount);
        cpu.imem2de_data(imem2de_ch);
        cpu.fe2imem_data(fe2imem_ch);
        cpu.dmem2wb_data(dmem2wb_ch);
        cpu.wb2dmem_data(wb2dmem_ch);
        cpu.mmio_in(mmio_in_ch);
        cpu.mmio_out(mmio_out_ch);     // narrowed by pkt_th below
        cpu.mmio_out_b(mmio_out_b_ch); // and pkt_b_th

        SC_CTHREAD(imemory_th, clk.pos());
        async_reset_signal_is(rst, false);
        SC_CTHREAD(dmemory_th, clk.pos());
        async_reset_signal_is(rst, false);
        SC_CTHREAD(pkt_th, clk.pos());
        async_reset_signal_is(rst, false);
        SC_CTHREAD(pkt_b_th, clk.pos());
        async_reset_signal_is(rst, false);
    }
};

// ---------------------------------------------------------------------------
// One-lane view of the same processor, for a 1xN grid.
//
// drim_eva always exposes two lanes, but the chip's rvprog calls the IP with
// ONE argument when M == 1 -- so a two-port IP fails there with
// "IndexError: list index out of range" on node.args[idx]. The Vitis IP solves
// this by having a separate top per arity (rv_eva_mmm_src vs
// rv_eva_mmm_src_2x2); this is the same idea without duplicating the body.
//
// pkt_out_b is bound to an internal channel nothing reads. That is safe rather
// than a deadlock waiting to happen: a 1x1 program only ever stores to
// MMIO_BASE, so the CPU never pushes to lane 1 at all. A program that DID store
// to MMIO_BASE+1 would block forever here, which is the correct behaviour for a
// channel with no consumer.
SC_MODULE(drim_eva1) {
    sc_in_clk   clk;
    sc_in<bool> rst;
    Connections::Out< ac_int<26, false> > CCS_INIT_S1(pkt_out);

    Connections::Combinational< ac_int<26, false> > CCS_INIT_S1(lane1_unused);
    drim_eva inner;

    SC_CTOR(drim_eva1) : inner("inner") {
        inner.clk(clk);
        inner.rst(rst);
        inner.pkt_out(pkt_out);
        inner.pkt_out_b(lane1_unused);
    }
};

#endif // __DRIM_EVA__H
