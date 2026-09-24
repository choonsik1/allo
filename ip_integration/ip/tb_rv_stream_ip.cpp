// Standalone testbench for rv_stream_ip -- verifies the processor IP on the
// host with g++, before any Allo involvement. Compiling against Vitis's real
// hls_stream.h means this exercises the same code csynth will see.
//
// The program reads two words per iteration and writes their sum, 32 times, so
// we can pre-fill all 64 inputs and drain 32 outputs sequentially: there is no
// feedback path, so nothing can deadlock in a single-threaded run.
#include <cstdio>
#include <cstdlib>

#include "rv_stream_ip.cpp"

// Checks rv_eva_collector against the protocol the Allo col_e kernel implements:
//   prime PRIME_TOKENS-1 zero credits, then one credit of 2;
//   per step: read a systolic word, return credit == its valid bit, forward the
//   raw word.
// Feeding all NSTEP words up front is safe here for the same reason as above --
// no feedback path, so a single-threaded run cannot deadlock.
static int test_collector() {
  hls::stream<sys_word_t> sys_in, res_out;
  hls::stream<int32_t> scr_out;

  const int NS = COLLECTOR_NSTEP;
  sys_word_t sent[NS];
  int expect_valid = 0;
  for (int t = 0; t < NS; t++) {
    // Alternate valid/bubble, with a recognisable payload in bits[1:17].
    sys_word_t w = 0;
    int vld = (t % 3 != 0);
    w[0] = vld;
    w(16, 1) = (ap_uint<16>)(0x1000 + t);
    sent[t] = w;
    expect_valid += vld;
    sys_in.write(w);
  }

  rv_eva_collector(sys_in, scr_out, res_out);

  // Credits: PRIME_TOKENS-1 zeros, then a 2, then one per step == valid bit.
  size_t want_credits = (size_t)(COLLECTOR_PRIME_TOKENS - 1) + 1 + NS;
  if (scr_out.size() != want_credits) {
    printf("FAIL: %zu credits, expected %zu\n", (size_t)scr_out.size(),
           want_credits);
    return 1;
  }
  for (int i = 0; i < COLLECTOR_PRIME_TOKENS - 1; i++) {
    if (scr_out.read() != 0) {
      printf("FAIL: prime credit %d was not 0\n", i);
      return 1;
    }
  }
  if (scr_out.read() != 2) {
    printf("FAIL: hold-capacity credit was not 2\n");
    return 1;
  }
  int credited = 0;
  for (int t = 0; t < NS; t++) {
    int32_t c = scr_out.read();
    int vld = (int)sent[t][0];
    if (c != vld) {
      printf("FAIL: credit[%d] = %d, expected %d\n", t, (int)c, vld);
      return 1;
    }
    credited += c;
  }
  if (credited != expect_valid) {
    printf("FAIL: credited %d words, %d were valid\n", credited, expect_valid);
    return 1;
  }

  // Every raw word is forwarded, valid or not, so the drain kernel can read a
  // fixed count.
  if (res_out.size() != (size_t)NS) {
    printf("FAIL: %zu forwarded words, expected %d\n", (size_t)res_out.size(),
           NS);
    return 1;
  }
  for (int t = 0; t < NS; t++) {
    sys_word_t got = res_out.read();
    if (got != sent[t]) {
      printf("FAIL: forwarded[%d] = %u, expected %u\n", t, (unsigned)got,
             (unsigned)sent[t]);
      return 1;
    }
  }
  if (!sys_in.empty()) {
    printf("FAIL: %zu systolic words left unread\n", (size_t)sys_in.size());
    return 1;
  }

  printf("PASS: RV32I collector honoured the col_e credit protocol "
         "(%d steps, %d valid)\n", NS, expect_valid);
  return 0;
}

// Checks rv_eva_programmer against the protocol the Allo rdrv_w kernel
// implements, and against the boot sequence the PE expects:
//   prime PRIME_TOKENS-1 empty packets;
//   per step: take a credit, emit a real packet only if one is owed AND a
//   credit is held, otherwise a bubble -- but always exactly one put.
static int test_programmer() {
  hls::stream<int32_t> cr_in;
  hls::stream<pkt_t> rtr_out;

  const int NS = PROGRAMMER_NSTEP;
  // One credit per step: the array can absorb a packet every cycle.
  for (int t = 0; t < NS; t++) cr_in.write(1);

  rv_eva_programmer(cr_in, rtr_out);

  size_t want = (size_t)(PROGRAMMER_PRIME_TOKENS - 1) + NS;
  if (rtr_out.size() != want) {
    printf("FAIL: %zu packets emitted, expected %zu\n", (size_t)rtr_out.size(),
           want);
    return 1;
  }
  for (int i = 0; i < PROGRAMMER_PRIME_TOKENS - 1; i++) {
    if (rtr_out.read() != 0) {
      printf("FAIL: prime packet %d was not empty\n", i);
      return 1;
    }
  }
  // The boot sequence, in order, then bubbles for the remaining steps.
  const ap_uint<32> *table = &PROGRAMMER_PROGRAM[PROGRAMMER_HALT_PC / 4];
  const int NPKT = PROGRAMMER_WORDS - PROGRAMMER_HALT_PC / 4;
  for (int t = 0; t < NS; t++) {
    pkt_t got = rtr_out.read();
    pkt_t want_pkt = (t < NPKT) ? (pkt_t)table[t] : (pkt_t)0;
    if (got != want_pkt) {
      printf("FAIL: packet[%d] = 0x%07x, expected 0x%07x\n", t, (unsigned)got,
             (unsigned)want_pkt);
      return 1;
    }
  }
  if (!cr_in.empty()) {
    printf("FAIL: %zu credits left unread\n", (size_t)cr_in.size());
    return 1;
  }

  // Spot-check that the sequence really is a PE boot: last packet sets fetch_en.
  pkt_t go = (pkt_t)table[NPKT - 1];
  int mode = (int)go[20], addr = (int)go(19, 16), data = (int)go(15, 0);
  if (mode != 1 || addr != 0 || !((data >> 15) & 1)) {
    printf("FAIL: last boot packet is not a fetch_en config write\n");
    return 1;
  }

  printf("PASS: RV32I programmer emitted the %d-packet PE boot sequence "
         "(ending in fetch_en) under the rdrv_w credit protocol\n", NPKT);
  return 0;
}

// Checks rv_eva_pktsrc, which feeds EVA's own rdrv_w rather than replacing it.
// No credits, no priming, no bubbles -- the driver owns all of that -- so the
// contract is just: emit exactly PKTSRC_NPKT packets, in ROM order, and stop.
//
// The 2x2 image is two nodes' worth back-to-back on one west lane, so this also
// checks the per-node structure the PE requires: 8 IRF writes (addr 8..15,
// mode 1), then the DRF writes (mode 0), then config_reg_1 (addr 1), then
// config_reg_0 with fetch_en LAST. Getting that order or the slot count wrong
// silently yields no output at all from the array, which costs a cosim to find.
static int test_pktsrc() {
  hls::stream<pkt_t> rtr_out, rtr_out1;

  rv_eva_pktsrc(rtr_out, rtr_out1);

  if (rtr_out1.size() != (size_t)PKTSRC_NPKT) {
    printf("FAIL: lane 1 got %zu packets, expected %d\n",
           (size_t)rtr_out1.size(), PKTSRC_NPKT);
    return 1;
  }
  if (rtr_out.size() != (size_t)PKTSRC_NPKT) {
    printf("FAIL: %zu packets emitted, expected %d\n", (size_t)rtr_out.size(),
           PKTSRC_NPKT);
    return 1;
  }

  const ap_uint<32> *table = &PKTSRC_PROGRAM[PKTSRC_HALT_PC / 4];
  if (PKTSRC_WORDS - PKTSRC_HALT_PC / 4 != 2 * PKTSRC_NPKT) {
    printf("FAIL: ROM holds %d packets but expected 2 lanes x %d\n",
           PKTSRC_WORDS - PKTSRC_HALT_PC / 4, PKTSRC_NPKT);
    return 1;
  }

  int nodes = 0;
  for (int i = 0; i < PKTSRC_NPKT; i++) {
    pkt_t got = rtr_out.read();
    if (got != (pkt_t)table[i]) {
      printf("FAIL: packet[%d] = 0x%07x, expected 0x%07x\n", i, (unsigned)got,
             (unsigned)table[i]);
      return 1;
    }
    int mode = (int)got[20], addr = (int)got(19, 16), data = (int)got(15, 0);
    int slot = i % 12;                    // 8 IRF + 2 DRF + 2 config per node
    if (slot < 8) {                       // IRF: mode 1, addr 8 + slot
      if (mode != 1 || addr != 8 + slot) {
        printf("FAIL: packet[%d] is not IRF slot %d (mode %d addr %d)\n", i,
               slot, mode, addr);
        return 1;
      }
    } else if (slot < 10) {               // DRF: mode 0 data write
      if (mode != 0) {
        printf("FAIL: packet[%d] is not a DRF write (mode %d)\n", i, mode);
        return 1;
      }
    } else if (slot == 10) {              // config_reg_1 = iteration count
      if (mode != 1 || addr != 1) {
        printf("FAIL: packet[%d] is not config_reg_1 (mode %d addr %d)\n", i,
               mode, addr);
        return 1;
      }
    } else {                              // config_reg_0, fetch_en, LAST
      if (mode != 1 || addr != 0 || !((data >> 15) & 1)) {
        printf("FAIL: packet[%d] does not set fetch_en last (mode %d addr %d "
               "data 0x%04x)\n", i, mode, addr, data);
        return 1;
      }
      nodes++;
    }
  }

  // Each node must be addressed by a distinct id, or two PEs take the same
  // program and the rest are never booted.
  if (nodes < 1) {
    printf("FAIL: no node in the image ends with a fetch_en write\n");
    return 1;
  }

  printf("PASS: RV32I program source drove 2 west lanes x %d packets = %d node "
         "boot sequences per lane\n", PKTSRC_NPKT, nodes);
  return 0;
}

// Checks rv_eva_mmm_src: same contract as rv_eva_pktsrc, but the image boots
// the PE to run the golden weight-stationary MMM kernel. Verifies the four
// kernel instructions land in irf[0..3] in order, the weight lands in drf[0],
// and cfg_isz is KLEN-1 with the batch count in cfg_itsz. cfg_isz is the LAST
// instruction index, not the count -- getting that wrong runs the wrong number
// of instructions per iteration and produces silent garbage.
static int test_mmm_src() {
  hls::stream<pkt_t> rtr_out;

  rv_eva_mmm_src(rtr_out);

  if (rtr_out.size() != (size_t)MMMSRC_NPKT) {
    printf("FAIL: %zu packets emitted, expected %d\n", (size_t)rtr_out.size(),
           MMMSRC_NPKT);
    return 1;
  }

  const int KERNEL[4] = {0xE13, 0x1022, 0x1F3, 0xC2D0};
  const int KLEN = 4;
  for (int i = 0; i < MMMSRC_NPKT; i++) {
    pkt_t got = rtr_out.read();
    int mode = (int)got[20], addr = (int)got(19, 16), data = (int)got(15, 0);
    if (i < KLEN) {                       // the MMM kernel itself
      if (mode != 1 || addr != 8 + i || data != KERNEL[i]) {
        printf("FAIL: irf[%d] = 0x%04x (mode %d addr %d), expected 0x%04x\n", i,
               data, mode, addr, KERNEL[i]);
        return 1;
      }
    } else if (i < 8) {                   // NOP padding
      if (mode != 1 || addr != 8 + i || data != 0x773) {
        printf("FAIL: irf[%d] is not NOP (0x%04x)\n", i, data);
        return 1;
      }
    } else if (i == 8) {                  // stationary weight
      if (mode != 0 || addr != 0) {
        printf("FAIL: packet[8] is not a drf[0] write (mode %d addr %d)\n",
               mode, addr);
        return 1;
      }
    } else if (i == 9) {                  // cfg_itsz = batch
      if (mode != 1 || addr != 1 || data != MMMSRC_BATCH) {
        printf("FAIL: cfg_itsz = %d, expected batch %d\n", data, MMMSRC_BATCH);
        return 1;
      }
    } else {                              // cfg_isz + fetch_en, LAST
      int isz = (data >> 8) & 0x7;
      if (mode != 1 || addr != 0 || !((data >> 15) & 1)) {
        printf("FAIL: last packet does not set fetch_en\n");
        return 1;
      }
      if (isz != KLEN - 1) {
        printf("FAIL: cfg_isz = %d, expected %d (LAST index, not the count)\n",
               isz, KLEN - 1);
        return 1;
      }
    }
  }

  printf("PASS: RV32I MMM source emitted the %d-packet boot for the golden "
         "weight-stationary kernel (isz=%d, itsz=%d)\n",
         MMMSRC_NPKT, KLEN - 1, MMMSRC_BATCH);
  return 0;
}

int main() {
  hls::stream<int32_t> sin, sout;

  const int N = 32;
  int32_t a[N], b[N];
  for (int i = 0; i < N; i++) {
    a[i] = i * 3 + 1;
    b[i] = i * 7 - 5;
    // Interleaved in the order the program consumes them: a, b, a, b, ...
    sin.write(a[i]);
    sin.write(b[i]);
  }

  rv_stream_ip(sin, sout);

  int errors = 0;
  if (sout.size() != N) {
    printf("FAIL: expected %d outputs, got %zu\n", N, (size_t)sout.size());
    return 1;
  }
  for (int i = 0; i < N; i++) {
    int32_t got = sout.read();
    int32_t want = a[i] + b[i];
    if (got != want) {
      if (errors < 5)
        printf("FAIL: out[%d] = %d, expected %d\n", i, got, want);
      errors++;
    }
  }
  if (!sin.empty()) {
    printf("FAIL: %zu input words left unread\n", (size_t)sin.size());
    return 1;
  }
  if (errors) {
    printf("FAIL: %d/%d mismatches\n", errors, N);
    return 1;
  }
  printf("PASS: RV32I core computed %d sums over hls::stream ports\n", N);

  if (test_collector()) return 1;
  if (test_programmer()) return 1;
  if (test_pktsrc()) return 1;
  return test_mmm_src();
}
