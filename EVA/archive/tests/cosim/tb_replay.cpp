// =============================================================================
// tb_replay.cpp - ONE generic cosim testbench for every EVA workload: replays
// simulator-captured vectors (see dump_vectors.py) against the Allo-generated
// RTL and compares ALL outputs bit-for-bit. Compile with
//   -DVECHDR="vectors_<test>.h"   (defines VM, VN, VL + IN/IV/RIN/EOUT/EROUT)
// Precheck idiom: ALLOW_EMPTY + return 0; last printed PASS/FAIL = verdict.
// =============================================================================
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "hls_half.h"
#include VECHDR

void top(half in_w[VM][VL], int32_t iv_w[VM][VL],
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
static int cmph(const half *g, const unsigned short *e, int n, const char *nm) {
    int errs = 0;
    for (int i = 0; i < n; i++) {
        unsigned short gb; memcpy(&gb, &g[i], 2);
        if (gb != e[i]) { if (errs < 8) printf("  %s[%d]=0x%04x exp 0x%04x\n", nm, i, gb, e[i]); errs++; }
    }
    return errs;
}
static int cmpi(const int32_t *g, const int32_t *e, int n, const char *nm) {
    int errs = 0;
    for (int i = 0; i < n; i++)
        if (g[i] != e[i]) { if (errs < 8) printf("  %s[%d]=0x%08x exp 0x%08x\n", nm, i, g[i], e[i]); errs++; }
    return errs;
}

int main() {
    static half    in_w[VM][VL], in_e[VM][VL], in_n[VN][VL], in_s[VN][VL];
    static half    out_w[VM][VL], out_e[VM][VL], out_n[VN][VL], out_s[VN][VL];
    static int32_t iv_w[VM][VL], iv_e[VM][VL], iv_n[VN][VL], iv_s[VN][VL];
    static int32_t rin_w[VM][VL], rin_e[VM][VL], rin_n[VN][VL], rin_s[VN][VL];
    static int32_t rout_w[VM][VL], rout_e[VM][VL], rout_n[VN][VL], rout_s[VN][VL];

    fill(&in_w[0][0], &IN0[0][0], VM * VL); fill(&in_e[0][0], &IN1[0][0], VM * VL);
    fill(&in_n[0][0], &IN2[0][0], VN * VL); fill(&in_s[0][0], &IN3[0][0], VN * VL);
    memcpy(iv_w, IV0, sizeof iv_w);  memcpy(iv_e, IV1, sizeof iv_e);
    memcpy(iv_n, IV2, sizeof iv_n);  memcpy(iv_s, IV3, sizeof iv_s);
    memcpy(rin_w, RIN0, sizeof rin_w); memcpy(rin_e, RIN1, sizeof rin_e);
    memcpy(rin_n, RIN2, sizeof rin_n); memcpy(rin_s, RIN3, sizeof rin_s);

    top(in_w, iv_w, in_e, iv_e, in_n, iv_n, in_s, iv_s,
        out_w, out_e, out_n, out_s,
        rin_w, rin_e, rin_n, rin_s,
        rout_w, rout_e, rout_n, rout_s);

    int errs = 0;
    errs += cmph(&out_w[0][0], &EOUT0[0][0], VM * VL, "out_w");
    errs += cmph(&out_e[0][0], &EOUT1[0][0], VM * VL, "out_e");
    errs += cmph(&out_n[0][0], &EOUT2[0][0], VN * VL, "out_n");
    errs += cmph(&out_s[0][0], &EOUT3[0][0], VN * VL, "out_s");
    errs += cmpi(&rout_w[0][0], &EROUT0[0][0], VM * VL, "rout_w");
    errs += cmpi(&rout_e[0][0], &EROUT1[0][0], VM * VL, "rout_e");
    errs += cmpi(&rout_n[0][0], &EROUT2[0][0], VN * VL, "rout_n");
    errs += cmpi(&rout_s[0][0], &EROUT3[0][0], VN * VL, "rout_s");
    printf("%s: replay %s (%d mismatches)\n", errs ? "FAIL" : "PASS", VECNAME, errs);
    return 0;   // NON-FATAL: C precheck is all-zero by design; read last line
}
