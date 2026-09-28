// tb_replay_golden_prime_ts.cpp - TIMESTAMPED golden replay for the ts chip
// (eva_sb_syscredit_rtprime_ts = rtprime + out_cyc). Same as tb_replay_golden_prime.cpp
// but top() now pairs an int32 out_cyc_X array with each out_X (the collector stamps the
// production cycle t). Reports, per row: golden match + the ARRIVAL CYCLE of each drained
// word -> answers fft "late vs never" (does a row ever drain, and at what cycle) + throughput.
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
         half out_w[VM][VL], int32_t out_cyc_w[VM][VL],
         half out_e[VM][VL], int32_t out_cyc_e[VM][VL],
         half out_n[VN][VL], int32_t out_cyc_n[VN][VL],
         half out_s[VN][VL], int32_t out_cyc_s[VN][VL],
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
    static int32_t out_cyc_w[VM][VL], out_cyc_e[VM][VL], out_cyc_n[VN][VL], out_cyc_s[VN][VL];
    static int32_t iv_w[VM][VL], iv_e[VM][VL], iv_n[VN][VL], iv_s[VN][VL];
    static int32_t rin_w[VM][VL], rin_e[VM][VL], rin_n[VN][VL], rin_s[VN][VL];
    static int32_t rout_w[VM][VL], rout_e[VM][VL], rout_n[VN][VL], rout_s[VN][VL];

    memcpy(prime_cfg, PRIMECFG, sizeof prime_cfg);
    printf("[ts one-bitstream] %s prime_cfg=%d  L=%d\n", VECNAME, prime_cfg[0][0], VL);
    fill(&in_w[0][0], &IN0[0][0], VM*VL); fill(&in_e[0][0], &IN1[0][0], VM*VL);
    fill(&in_n[0][0], &IN2[0][0], VN*VL); fill(&in_s[0][0], &IN3[0][0], VN*VL);
    memcpy(iv_w,IV0,sizeof iv_w); memcpy(iv_e,IV1,sizeof iv_e); memcpy(iv_n,IV2,sizeof iv_n); memcpy(iv_s,IV3,sizeof iv_s);
    memcpy(rin_w,RIN0,sizeof rin_w); memcpy(rin_e,RIN1,sizeof rin_e); memcpy(rin_n,RIN2,sizeof rin_n); memcpy(rin_s,RIN3,sizeof rin_s);

    top(prime_cfg,
        in_w,iv_w, in_e,iv_e, in_n,iv_n, in_s,iv_s,
        out_w,out_cyc_w, out_e,out_cyc_e, out_n,out_cyc_n, out_s,out_cyc_s,
        rin_w,rin_e,rin_n,rin_s, rout_w,rout_e,rout_n,rout_s);

    half   (*out)[VL] = (VOUT_IDX == 1) ? out_e : out_s;
    int32_t(*ocyc)[VL] = (VOUT_IDX == 1) ? out_cyc_e : out_cyc_s;
    const unsigned short (*gold)[VL] = (const unsigned short(*)[VL])((VOUT_IDX==1)?&EOUT1[0][0]:&EOUT3[0][0]);
    const char *edge = (VOUT_IDX == 1) ? "out_e(east)" : "out_s(south)";

    printf("8x8 TIMESTAMPED replay (%s) — %s vs golden (%d vals/row)\n", VECNAME, edge, VGMAX);
    int rows_ok = 0;
    for (int k = 0; k < VN; k++) {
        unsigned short g[VGMAX]; int ng = 0;
        for (int t = 0; t < VGMAX; t++) { g[t] = gold[k][t]; if (g[t]) ng = t + 1; }
        if (ng == 0) { printf("  row %d: (no golden)\n", k); rows_ok++; continue; }
        int found = -1;
        for (int s = 0; s + ng <= VL; s++) {
            int ok = 1;
            for (int t = 0; t < ng; t++) if (hb(&out[k][s + t]) != g[t]) { ok = 0; break; }
            if (ok) { found = s; break; }
        }
        // how many nonzero words did this row EVER drain, and at what cycles?
        int ndr = 0, first_cyc = -1, last_cyc = -1;
        for (int t = 0; t < VL; t++) if (hb(&out[k][t])) { if (first_cyc < 0) first_cyc = ocyc[k][t]; last_cyc = ocyc[k][t]; ndr++; }
#ifdef DUMP_CYC
        // per-word production-cycle trace: every drained word's slot, value, cycle, and gap
        // from the previous word (gap>steady ⇒ a bubble). Enable with -DDUMP_CYC.
        { int prev = -1, w = 0;
          for (int t = 0; t < VL; t++) if (hb(&out[k][t])) {
              int c = ocyc[k][t];
              printf("    CYCDUMP row %d word %d: slot=%d val=%04x cyc=%d gap=%d\n",
                     k, w, t, (unsigned)hb(&out[k][t]), c, (prev < 0) ? 0 : c - prev);
              prev = c; w++;
          } }
#endif
        printf("  row %d: %s golden", k, found >= 0 ? "OK " : "x  ");
        for (int t=0;t<ng;t++) printf(" %04x", g[t]);
        printf(found>=0 ? "  @slot %d" : "  NOT found", found>=0?found:0);
        printf("  | drained %d words, arrival cyc first=%d last=%d\n", ndr, first_cyc, last_cyc);
        // FULL-STREAM check: EVERY drained word must equal golden[i % ng] (golden repeated per batch).
        // 'found @slot 0' only proves the pattern appears once; this verifies all B outputs are correct.
        {
            int idx = 0, full_chk = 0, full_miss = 0, first_miss = -1;
            for (int t = 0; t < VL; t++) if (hb(&out[k][t])) {
                unsigned short exp = g[idx % ng];
                if (hb(&out[k][t]) != exp) { if (first_miss < 0) first_miss = idx; full_miss++; }
                idx++; full_chk++;
            }
            printf("  row %d FULL-STREAM: %d/%d words match golden-repeat%s", k,
                   full_chk - full_miss, full_chk, (full_miss == 0 && full_chk > 0) ? "  [ALL-OK]" : "");
            if (full_miss) printf("  first-mismatch@word %d", first_miss);
            printf("\n");
        }
        if (found >= 0) rows_ok++;
    }
    int clean = (rows_ok == VN);
    printf("%s: ts cosim %s prime=%d L=%d (%d/%d rows bit-exact vs golden)\n",
           clean ? "PASS" : "FAIL", VECNAME, prime_cfg[0][0], VL, rows_ok, VN);
    return 0;
}
