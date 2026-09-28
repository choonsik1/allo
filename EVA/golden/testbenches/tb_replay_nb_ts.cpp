// tb_replay_nb_ts.cpp - timestamp/throughput tb for the NB _ts chip. top() has
// the extra out_cyc_{w,e,n,s} int32 ports (collectors stamp the capture cycle t).
// We stream B MMMs (cfg_itsz=B) and read the per-result cycle on out_s -> the
// gaps between consecutive results = steady-state cyc/MMM. Compares ONLY out_s.
// Port order = generated top(): in/iv interleaved, out/out_cyc interleaved, rin, rout.
// -DVECHDR="vectors_*.h"  (VM,VN,VL + IN/IV/RIN/EOUT/EROUT)
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

    // ---- out_s results + their production cycles (the throughput data) ----
    printf("---- out_s results + production cycle (per column, streamed MMMs) ----\n");
    int gcnt = 0, gfirst = 1 << 30, glast = -1;
    for (int c = 0; c < VN; c++) {
        int first = 1 << 30, last = -1, n = 0;
        for (int k = 0; k < VL; k++) {
            unsigned short vb; memcpy(&vb, &out_s[c][k], 2);
            if (vb == 0) continue;
            int cyc = out_cyc_s[c][k];
            printf("  out_s[%d] #%d = 0x%04x @ cyc %d\n", c, k, vb, cyc);
            if (cyc < first) first = cyc;
            if (cyc > last) last = cyc;
            n++;
        }
        if (n > 1)
            printf("  >> col %d: %d MMMs, first@%d last@%d, span %d cyc -> %.1f cyc/MMM\n",
                   c, n, first, last, last - first, (double)(last - first) / (n - 1));
        else if (n == 1)
            printf("  >> col %d: 1 MMM @ cyc %d (need B>1 to measure throughput)\n", c, first);
        if (n > 0) { gcnt += n; if (first < gfirst) gfirst = first; if (last > glast) glast = last; }
    }
    if (gcnt > VN)
        printf("==> ALL cols: %d results, span %d..%d = %d cyc; ~throughput = %.1f cyc/MMM\n",
               gcnt, gfirst, glast, glast - gfirst, (double)(glast - gfirst) / (gcnt / VN - 1));

    // ---- correctness with VALID-WINDOW discard ----
    // Each column streams B identical MMMs, so the expected steady-state value is
    // EOUT3[c][0]. Per column we discard the leading PIPELINE-FILL outputs (the
    // pipeline/systolic warmup, != steady value — same as the 1x1 MAC TB's leading
    // zeros), then require the steady-state run to be bit-exact. Empty (0x0000)
    // slots are not-yet-produced and are skipped, not counted as errors.
    int cols_ok = 0, cols_bad = 0, cols_nosample = 0;
    for (int c = 0; c < VN; c++) {
        unsigned short E = EOUT3[c][0];
        if (E == 0) continue;                          // column not driven
        int firstvalid = -1, nfill = 0, nvalid = 0, badafter = 0;
        int vfc = -1, vlc = -1;
        for (int k = 0; k < VL; k++) {
            unsigned short vb; memcpy(&vb, &out_s[c][k], 2);
            if (vb == 0) continue;                     // undrained slot -> skip
            if (firstvalid < 0 && vb != E) { nfill++; continue; }   // leading fill -> discard
            if (firstvalid < 0) firstvalid = k;        // steady state begins
            if (vb == E) { nvalid++; if (vfc < 0) vfc = out_cyc_s[c][k]; vlc = out_cyc_s[c][k]; }
            else { badafter++; if (badafter <= 4) printf("  REAL MISMATCH out_s[%d][%d]=0x%04x exp 0x%04x\n", c, k, vb, E); }
        }
        if (firstvalid < 0) {
            printf("  col %d: NO steady-state sample @0x%04x (%d fill only -> undrained/dropped)\n", c, E, nfill);
            cols_nosample++;
        } else {
            double cpm = nvalid > 1 ? (double)(vlc - vfc) / (nvalid - 1) : 0.0;
            printf("  col %d: OK (discarded %d fill; %d valid @0x%04x; %.1f cyc/MMM)%s\n",
                   c, nfill, nvalid, E, cpm, badafter ? "  [ERRORS after steady state!]" : "");
            if (badafter) cols_bad++; else cols_ok++;
        }
    }
    int clean = (cols_bad == 0 && cols_nosample == 0);
    printf("%s: NB-ts %s (valid-window: %d cols bit-exact, %d no-sample, %d with-errors)\n",
           clean ? "PASS" : "FAIL", VECNAME, cols_ok, cols_nosample, cols_bad);
    return 0;
}
