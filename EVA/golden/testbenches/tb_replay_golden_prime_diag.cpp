// tb_replay_golden_prime_diag.cpp - DIAGNOSTIC variant of tb_replay_golden_prime.cpp.
// Same replay, but after the normal check it HUNTS each FAILING row's golden value across
// EVERY output edge (systolic out_* as half, router rout_* as packet data field). Tells us:
//   - found in rout_e[k]  -> result produced + routed east, but systolic collector missed it (DRAIN bug)
//   - found in out_s/out_n/out_w or rout_w/n/s -> produced but mis-routed (ROUTER bug)
//   - found NOWHERE -> MAC never fired for that row (operand never delivered)
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "hls_half.h"
#include VECHDR

void top(int32_t prime_cfg[VM][VN],
         half in_w[VM][VL], int32_t iv_w[VM][VL],
         half in_e[VM][VL], int32_t iv_e[VM][VL],
         half in_n[VN][VL], int32_t iv_n[VN][VL],
         half in_s[VN][VL], int32_t iv_s[VN][VL],
         half out_w[VM][VL], half out_e[VM][VL],
         half out_n[VN][VL], half out_s[VN][VL],
         int32_t rin_w[VM][VL], int32_t rin_e[VM][VL],
         int32_t rin_n[VN][VL], int32_t rin_s[VN][VL],
         int32_t rout_w[VM][VL], int32_t rout_e[VM][VL],
         int32_t rout_n[VN][VL], int32_t rout_s[VN][VL]);

static void fill(half *d, const unsigned short *b, int n) { for (int i=0;i<n;i++) memcpy(&d[i],&b[i],2); }
static inline unsigned short hb(const half *h){ unsigned short u; memcpy(&u,h,2); return u; }

int main() {
    static int32_t prime_cfg[VM][VN];
    static half    in_w[VM][VL], in_e[VM][VL], in_n[VN][VL], in_s[VN][VL];
    static half    out_w[VM][VL], out_e[VM][VL], out_n[VN][VL], out_s[VN][VL];
    static int32_t iv_w[VM][VL], iv_e[VM][VL], iv_n[VN][VL], iv_s[VN][VL];
    static int32_t rin_w[VM][VL], rin_e[VM][VL], rin_n[VN][VL], rin_s[VN][VL];
    static int32_t rout_w[VM][VL], rout_e[VM][VL], rout_n[VN][VL], rout_s[VN][VL];

    memcpy(prime_cfg, PRIMECFG, sizeof prime_cfg);
    printf("[DIAG one-bitstream] %s prime_cfg=%d\n", VECNAME, prime_cfg[0][0]);
    fill(&in_w[0][0], &IN0[0][0], VM*VL); fill(&in_e[0][0], &IN1[0][0], VM*VL);
    fill(&in_n[0][0], &IN2[0][0], VN*VL); fill(&in_s[0][0], &IN3[0][0], VN*VL);
    memcpy(iv_w,IV0,sizeof iv_w); memcpy(iv_e,IV1,sizeof iv_e); memcpy(iv_n,IV2,sizeof iv_n); memcpy(iv_s,IV3,sizeof iv_s);
    memcpy(rin_w,RIN0,sizeof rin_w); memcpy(rin_e,RIN1,sizeof rin_e); memcpy(rin_n,RIN2,sizeof rin_n); memcpy(rin_s,RIN3,sizeof rin_s);

    top(prime_cfg, in_w,iv_w, in_e,iv_e, in_n,iv_n, in_s,iv_s,
        out_w,out_e,out_n,out_s, rin_w,rin_e,rin_n,rin_s, rout_w,rout_e,rout_n,rout_s);

    half (*out)[VL] = (VOUT_IDX == 1) ? out_e : out_s;
    const unsigned short (*gold)[VL] = (const unsigned short(*)[VL])((VOUT_IDX==1)?&EOUT1[0][0]:&EOUT3[0][0]);

    printf("---- DIAG: hunt each FAILING row's golden[0] across ALL edges ----\n");
    for (int k = 0; k < VN; k++) {
        unsigned short g0 = gold[k][0];
        if (!g0) continue;
        int okrow = 0;
        for (int s = 0; s < VL; s++) if (hb(&out[k][s]) == g0) { okrow = 1; break; }
        if (okrow) { printf("  row %d OK (golden %04x on target edge)\n", k, g0); continue; }
        printf("  row %d FAIL, golden[0]=%04x -> searching all edges:\n", k, g0);
        int hits = 0;
        #define SCANH(A,D) do{ for(int i=0;i<D;i++) for(int s=0;s<VL;s++) if(hb(&A[i][s])==g0){printf("      HIT %s[%d][%d]\n",#A,i,s); hits++;} }while(0)
        SCANH(out_e,VM); SCANH(out_w,VM); SCANH(out_n,VN); SCANH(out_s,VN);
        #define SCANR(A,D) do{ for(int i=0;i<D;i++) for(int s=0;s<VL;s++) if((unsigned short)(A[i][s]&0xFFFF)==g0){printf("      HIT %s[%d][%d] pkt=%08x\n",#A,i,s,(unsigned)A[i][s]); hits++;} }while(0)
        SCANR(rout_e,VM); SCANR(rout_w,VM); SCANR(rout_n,VN); SCANR(rout_s,VN);
        if (!hits) printf("      NOWHERE — value never appears on any edge (MAC likely never fired)\n");
    }
    printf("DIAG done for %s prime=%d\n", VECNAME, prime_cfg[0][0]);
    return 0;
}
