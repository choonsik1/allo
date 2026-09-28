// tb_replay_golden_prime.cpp - general golden replay for the RUNTIME-PRIME chip
// (eva_sb_syscredit_rtprime). Identical to tb_replay_golden.cpp but top() takes a
// leading per-tile prime_cfg[VM][VN] input (emitted FIRST). The SAME synthesized RTL
// runs every workload; only prime_cfg (VPRIME: 1 for fft/cordic, 6 for mmm) + the
// program/inputs differ -> the one-bitstream capstone.
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

static void fill(half *d, const unsigned short *b, int n) {
    for (int i = 0; i < n; i++) memcpy(&d[i], &b[i], 2);
}
static inline unsigned short hb(const half *h) { unsigned short u; memcpy(&u, h, 2); return u; }
static void dump_r(const char *nm, const int *o, int rows) {
    for (int r = 0; r < rows; r++) for (int k = 0; k < VL; k++)
        if (o[r*VL+k] != 0) printf("  %s[%d] #%d = %d\n", nm, r, k, o[r*VL+k]);
}
static void dump(const char *nm, const half *o, int rows) {
    for (int r = 0; r < rows; r++) for (int k = 0; k < VL; k++) {
        unsigned short vb; memcpy(&vb, &o[r*VL+k], 2);
        if (vb != 0) printf("  %s[%d] #%d = 0x%04x\n", nm, r, k, vb);
    }
}

int main() {
    static int32_t prime_cfg[VM][VN];
    static half    in_w[VM][VL], in_e[VM][VL], in_n[VN][VL], in_s[VN][VL];
    static half    out_w[VM][VL], out_e[VM][VL], out_n[VN][VL], out_s[VN][VL];
    static int32_t iv_w[VM][VL], iv_e[VM][VL], iv_n[VN][VL], iv_s[VN][VL];
    static int32_t rin_w[VM][VL], rin_e[VM][VL], rin_n[VN][VL], rin_s[VN][VL];
    static int32_t rout_w[VM][VL], rout_e[VM][VL], rout_n[VN][VL], rout_s[VN][VL];

    memcpy(prime_cfg, PRIMECFG, sizeof prime_cfg);
    printf("[one-bitstream] workload %s driven with prime_cfg=%d\n", VECNAME, prime_cfg[0][0]);

    fill(&in_w[0][0], &IN0[0][0], VM * VL); fill(&in_e[0][0], &IN1[0][0], VM * VL);
    fill(&in_n[0][0], &IN2[0][0], VN * VL); fill(&in_s[0][0], &IN3[0][0], VN * VL);
    memcpy(iv_w, IV0, sizeof iv_w);  memcpy(iv_e, IV1, sizeof iv_e);
    memcpy(iv_n, IV2, sizeof iv_n);  memcpy(iv_s, IV3, sizeof iv_s);
    memcpy(rin_w, RIN0, sizeof rin_w); memcpy(rin_e, RIN1, sizeof rin_e);
    memcpy(rin_n, RIN2, sizeof rin_n); memcpy(rin_s, RIN3, sizeof rin_s);

    top(prime_cfg,
        in_w, iv_w, in_e, iv_e, in_n, iv_n, in_s, iv_s,
        out_w, out_e, out_n, out_s,
        rin_w, rin_e, rin_n, rin_s,
        rout_w, rout_e, rout_n, rout_s);

    printf("---- ALL EDGES (diag) ----\n");
    dump("out_w",&out_w[0][0],VM); dump("out_e",&out_e[0][0],VM);
    dump("out_n",&out_n[0][0],VN); dump("out_s",&out_s[0][0],VN);
    printf("---- router escapes ----\n");
    dump_r("rout_w",&rout_w[0][0],VM); dump_r("rout_e",&rout_e[0][0],VM);
    dump_r("rout_n",&rout_n[0][0],VN); dump_r("rout_s",&rout_s[0][0],VN);
    printf("--------------------------\n");
    half (*out)[VL] = (VOUT_IDX == 1) ? out_e : out_s;
    const unsigned short (*gold)[VL] = (const unsigned short(*)[VL])
        ((VOUT_IDX == 1) ? &EOUT1[0][0] : &EOUT3[0][0]);
    const char *edge = (VOUT_IDX == 1) ? "out_e(east)" : "out_s(south)";

    printf("8x8 golden replay (%s) — %s vs golden (%d vals/row)\n", VECNAME, edge, VGMAX);
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
        char seen[80]; int p = 0, cnt = 0;
        for (int t = 0; t < VL && cnt < 6; t++) { unsigned short v = hb(&out[k][t]); if (v) { p += snprintf(seen+p, sizeof(seen)-p, "%04x ", v); cnt++; } }
        printf("  row %d: %s golden", k, found >= 0 ? "OK " : "x  ");
        for (int t=0;t<ng;t++) printf(" %04x", g[t]);
        printf(found >= 0 ? "  found @slot %d  (nz: %s)\n" : "  NOT found  (nz: %s)\n", found >= 0 ? found : 0, seen);
        if (found >= 0) rows_ok++;
    }
    int clean = (rows_ok == VN);
    printf("%s: golden cosim %s prime=%d (%d/%d rows bit-exact vs golden)\n",
           clean ? "PASS" : "FAIL", VECNAME, prime_cfg[0][0], rows_ok, VN);
    return 0;
}
