// tb_replay_golden_ts.cpp - TIMESTAMPED generalized golden replay for the _cosim
// chip (out_cyc_{w,e,n,s} ports stamp each output's production cycle). Same replay
// as tb_replay_golden.cpp (program from South, inputs West, compare workload's
// output edge vs golden), but ALSO reads out_cyc at each matched golden value ->
// production cycle + per-row gaps + array span (cyc/result throughput).
// Port order = generated _cosim top(): in/iv interleaved, out/out_cyc interleaved.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "hls_half.h"
#include VECHDR

void top(half in_w[VM][VL], int32_t iv_w[VM][VL],
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

static void fill(half *d, const unsigned short *b, int n) {
    for (int i = 0; i < n; i++) memcpy(&d[i], &b[i], 2);
}
static inline unsigned short hb(const half *h) { unsigned short u; memcpy(&u, h, 2); return u; }

int main() {
    static half    in_w[VM][VL], in_e[VM][VL], in_n[VN][VL], in_s[VN][VL];
    static int32_t iv_w[VM][VL], iv_e[VM][VL], iv_n[VN][VL], iv_s[VN][VL];
    static half    out_w[VM][VL], out_e[VM][VL], out_n[VN][VL], out_s[VN][VL];
    static int32_t out_cyc_w[VM][VL], out_cyc_e[VM][VL], out_cyc_n[VN][VL], out_cyc_s[VN][VL];
    static int32_t rin_w[VM][VL], rin_e[VM][VL], rin_n[VN][VL], rin_s[VN][VL];
    static int32_t rout_w[VM][VL], rout_e[VM][VL], rout_n[VN][VL], rout_s[VN][VL];

    fill(&in_w[0][0], &IN0[0][0], VM * VL); fill(&in_e[0][0], &IN1[0][0], VM * VL);
    fill(&in_n[0][0], &IN2[0][0], VN * VL); fill(&in_s[0][0], &IN3[0][0], VN * VL);
    memcpy(iv_w, IV0, sizeof iv_w);  memcpy(iv_e, IV1, sizeof iv_e);
    memcpy(iv_n, IV2, sizeof iv_n);  memcpy(iv_s, IV3, sizeof iv_s);
    memcpy(rin_w, RIN0, sizeof rin_w); memcpy(rin_e, RIN1, sizeof rin_e);
    memcpy(rin_n, RIN2, sizeof rin_n); memcpy(rin_s, RIN3, sizeof rin_s);

    top(in_w, iv_w, in_e, iv_e, in_n, iv_n, in_s, iv_s,
        out_w, out_cyc_w, out_e, out_cyc_e, out_n, out_cyc_n, out_s, out_cyc_s,
        rin_w, rin_e, rin_n, rin_s,
        rout_w, rout_e, rout_n, rout_s);

    half    (*out)[VL] = (VOUT_IDX == 1) ? out_e : out_s;
    int32_t (*ocyc)[VL] = (VOUT_IDX == 1) ? out_cyc_e : out_cyc_s;
    const unsigned short (*gold)[VL] = (const unsigned short(*)[VL])
        ((VOUT_IDX == 1) ? &EOUT1[0][0] : &EOUT3[0][0]);
    const char *edge = (VOUT_IDX == 1) ? "out_e(east)" : "out_s(south)";

    printf("8x8 TIMESTAMPED golden replay (%s) — %s vs golden (%d vals/row)\n", VECNAME, edge, VGMAX);
    int rows_ok = 0, gfirst = 1<<30, glast = -1, ngap = 0; double gapsum = 0;
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
        if (found < 0) { printf("  row %d: x  golden", k); for(int t=0;t<ng;t++) printf(" %04x",g[t]); printf(" NOT found\n"); continue; }
        rows_ok++;
        int c0 = ocyc[k][found], c1 = ocyc[k][found + ng - 1];
        double per = (ng > 1) ? (double)(c1 - c0) / (ng - 1) : 0.0;
        printf("  row %d: OK  golden", k); for(int t=0;t<ng;t++) printf(" %04x",g[t]);
        printf("  @cyc %d..%d (span %d, %.1f cyc/val)\n", c0, c1, c1 - c0, per);
        if (c0 < gfirst) gfirst = c0; if (c1 > glast) glast = c1;
        if (ng > 1) { gapsum += (c1 - c0) / (double)(ng - 1); ngap++; }
    }
    if (ngap > 0)
        printf("==> per-row avg spacing = %.1f cyc/val;  array span rows %d..%d = %d cyc\n",
               gapsum / ngap, gfirst, glast, glast - gfirst);
    int clean = (rows_ok == VN);
    printf("%s: golden-ts cosim %s (%d/%d rows bit-exact + timestamped)\n",
           clean ? "PASS" : "FAIL", VECNAME, rows_ok, VN);
    return 0;
}
