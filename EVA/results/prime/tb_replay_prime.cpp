// tb_replay_prime.cpp - cosim tb for the RUNTIME-PRIME chip. Same as
// tb_replay_nb.cpp but top() takes a leading per-tile input prime_cfg[VM][VN]
// (emitted FIRST in the port list, discovered via node args=[prime_cfg]).
// prime_cfg is filled with VPRIME so every PE/driver primes VPRIME-1 tokens at
// runtime. Compares out_s vs analytical X@W. -DVECHDR="vectors_*.h".
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

int main() {
    static int32_t prime_cfg[VM][VN];
    static half    in_w[VM][VL], in_e[VM][VL], in_n[VN][VL], in_s[VN][VL];
    static half    out_w[VM][VL], out_e[VM][VL], out_n[VN][VL], out_s[VN][VL];
    static int32_t iv_w[VM][VL], iv_e[VM][VL], iv_n[VN][VL], iv_s[VN][VL];
    static int32_t rin_w[VM][VL], rin_e[VM][VL], rin_n[VN][VL], rin_s[VN][VL];
    static int32_t rout_w[VM][VL], rout_e[VM][VL], rout_n[VN][VL], rout_s[VN][VL];

    memcpy(prime_cfg, PRIMECFG, sizeof prime_cfg);      // every cell = VPRIME
    printf("prime_cfg[0][0] = %d (runtime prime tokens)\n", prime_cfg[0][0]);

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

    printf("---- out_s (mmm result) ----\n");
    for (int c = 0; c < VN; c++) printf("  out_s seen[%d] = %.0f\n", c, (float)out_s[c][VL-1]);

    // only out_s (the mmm result), slots 0..VL-2 (last slot = debug count)
    int errs = 0;
    for (int c = 0; c < VN; c++)
        for (int k = 0; k < VL - 1; k++) {
            unsigned short gb; memcpy(&gb, &out_s[c][k], 2);
            if (gb != EOUT3[c][k]) { if (errs < 8) printf("  out_s[%d][%d]=0x%04x exp 0x%04x\n", c, k, gb, EOUT3[c][k]); errs++; }
        }
    printf("%s: RUNTIME-PRIME replay %s vs analytical X@W (prime=%d, out_s: %d mismatches)\n",
           errs ? "FAIL" : "PASS", VECNAME, VPRIME, errs);
    return 0;
}
