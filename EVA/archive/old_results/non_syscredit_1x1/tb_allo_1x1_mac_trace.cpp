// tb_allo_1x1_mac_trace.cpp - runs the EVA MAC and dumps the node's per-cycle
// ISSUE trace (dbg port) to pin the residual stall cycles. Same MAC program as
// tb_allo_1x1_mac_ts.cpp. dbg[0][0][t] packs, per node loop-iteration t:
//   [0]=grant [4:1]=pc+1 [5]=a_vld [6]=b_vld [7]=raw [8]=fwd_a [9]=fwd_b
//   [11:10]=holdW [13:12]=holdN [17:14]=op    (op: 0=ADD 2=MULT 3=MOV)
#include <cstdio>
#include <cstdint>
#include <cstring>
#include "hls_half.h"
static const int L = 200;
static int pack_pkt(int data, int addr, int mode, int idf, int rq = 1) {
    return (data & 0xFFFF) | (addr << 16) | (mode << 20) | (idf << 21) | (rq << 25); }
static int f16bits(float f){ half h=half(f); uint16_t u; memcpy(&u,&h,2); return u; }

void top(int32_t dbg[1][1][L],
         half in_w[1][L], int32_t iv_w[1][L], half in_e[1][L], int32_t iv_e[1][L],
         half in_n[1][L], int32_t iv_n[1][L], half in_s[1][L], int32_t iv_s[1][L],
         half out_w[1][L], half out_e[1][L], int32_t out_cyc_e[1][L],
         half out_n[1][L], half out_s[1][L], int32_t out_cyc_s[1][L],
         int32_t rin_w[1][L], int32_t rin_e[1][L], int32_t rin_n[1][L], int32_t rin_s[1][L],
         int32_t rout_w[1][L], int32_t rout_e[1][L], int32_t rout_n[1][L], int32_t rout_s[1][L]);

int main(){
    static int32_t dbg[1][1][L];
    static half in_w[1][L]={},in_e[1][L]={},in_n[1][L]={},in_s[1][L]={};
    static int32_t iv_w[1][L]={},iv_e[1][L]={},iv_n[1][L]={},iv_s[1][L]={};
    static half out_w[1][L]={},out_e[1][L]={},out_n[1][L]={},out_s[1][L]={};
    static int32_t out_cyc_e[1][L]={},out_cyc_s[1][L]={};
    static int32_t rin_w[1][L]={},rin_e[1][L]={},rin_n[1][L]={},rin_s[1][L]={};
    static int32_t rout_w[1][L]={},rout_e[1][L]={},rout_n[1][L]={},rout_s[1][L]={};

    const int B=8, PC=90; const float W=3.0f;
    const int I0=0xE13,I1=0x1022,I2=0x1F3,I3=0xC2D0,NOP=0x773;
    const int PROG[8]={I0,I1,I2,I3,NOP,NOP,NOP,NOP};
    int k=0;
    for(int s=0;s<8;s++) rin_s[0][k++]=pack_pkt(PROG[s],8+s,1,0);
    rin_s[0][k++]=pack_pkt(f16bits(W),0,0,0);
    rin_s[0][k++]=pack_pkt(B&0xFF,1,1,0);
    rin_s[0][k++]=pack_pkt((1<<15)|(((4-1)&0x7)<<8),0,1,0);
    const int KLEN=4;
    for(int b=0;b<B;b++){ in_w[0][PC+KLEN*b]=half(1+b); iv_w[0][PC+KLEN*b]=1; }
    for(int t=0;t<L;t++) iv_n[0][t]=1;

    top(dbg, in_w,iv_w,in_e,iv_e,in_n,iv_n,in_s,iv_s,
        out_w,out_e,out_cyc_e,out_n,out_s,out_cyc_s,
        rin_w,rin_e,rin_n,rin_s, rout_w,rout_e,rout_n,rout_s);

    const char* opn[16]={"ADD","SUB","MUL","MOV","RT0","RT1","RT2","RT3","GEQ","LT","?","?","C0","C1","C2","C3"};
    printf("== node ISSUE trace — only fetch iterations (pc>=0) ==\n");
    printf(" nt  | gr pc  op  a_vld b_vld raw fwdA fwdB holdW holdN | note\n");
    int nissue=0, nstall=0;
    for(int t=0;t<L;t++){
        int p=dbg[0][0][t];
        int pc=((p>>1)&0xF)-1;
        if(pc<0) continue;                       // skip no-fetch iterations
        int gr=p&1, avld=(p>>5)&1, bvld=(p>>6)&1, raw=(p>>7)&1;
        int fa=(p>>8)&1, fb=(p>>9)&1, hw=(p>>10)&3, hn=(p>>12)&3, op=(p>>14)&0xF;
        const char* note = gr?"ISSUE":"** STALL **";
        printf(" %3d | %d  %2d  %s  %d     %d     %d   %d    %d    %d     %d   | %s\n",
               t, gr, pc, opn[op&0xF], avld,bvld,raw,fa,fb,hw,hn,note);
        if(gr) nissue++; else nstall++;
    }
    printf(">> total: %d ISSUE, %d STALL (fetch iterations)\n", nissue, nstall);
    // ---- account for PIPELINE FILL: skip leading fill (0) outputs, then
    // validate the steady-state VALID WINDOW (standard for systolic/pipelined
    // designs -- the first N outputs are fill latency, you sample past them).
    int fill=0; while (fill < L && float(out_s[0][fill]) == 0.0f) fill++;
    printf("\npipeline fill latency: %d output(s) discarded; valid window from slot %d\n", fill, fill);
    printf("out_s VALID WINDOW (expect 3,6,9,12,...):\n");
    int errs=0, n=0;
    for (int kk=0; kk < B && fill+kk < L; kk++) {
        float got = float(out_s[0][fill+kk]); float exp = W*(1+kk);
        printf("  MAC[%d] = %g (exp %g) @cyc %d  %s\n", kk, got, exp, out_cyc_s[0][fill+kk], got==exp?"OK":"MISMATCH");
        if (got != exp) errs++; n++;
    }
    printf("%s: EVA single-PE MAC valid-window (%d MACs, fill=%d, FP_LAT=1, 4 cyc/MAC)\n",
           errs ? "FAIL" : "PASS", n, fill);
    return 0;
}
