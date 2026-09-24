// RTL co-simulation testbench for every EVA + processor design in this project.
//
// One file, selected by a -DTARGET_* flag from cosim_rv.ini (written by
// test_rv_stream_ip.py's emit_project). The five designs share a 21-argument
// top, an all-zero host stimulus, and the same result-scanning code; only the
// grid size, lane length and the expected answer differ.
//
//   TARGET_ADD1X1   1x1, processor REPLACES rdrv_w and drives the router plane
//                   itself. Expect fp16 3.0 on out_e.
//   TARGET_ADD2X2   2x2, one processor FEEDS both lane drivers. Column 0 sends
//                   its result west, column 1 east. Expect 3.0 x4.
//   TARGET_MMM1X1   1x1 running EVA's golden weight-stationary MMM kernel with
//                   W = 3. Expect out_s = [6, 12, 3].
//   TARGET_MMM2X2   2x2 computing a real matrix product, each node holding its
//                   own weight. Expect out_s col0 = [22,16,15], col1 = [34,24,29].
//
// In every case the ONLY host stimulus is prime_cfg, plus -- for the MMM
// targets -- activations on the west systolic edge and a valid-zero north seed.
// Nothing is ever fed on the router plane: the array's whole program comes from
// the RV32I processor's ROM.
//
// The argument order below is the EMITTED order (prime_cfg first, then the
// in/iv pairs, then out_*, rin_*, rout_*), which follows kernel-appearance
// order and not the Python region signature.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "hls_half.h"

#if defined(TARGET_ADD1X1)
  #define VM 1
  #define VN 1
  #define VL 100
#elif defined(TARGET_ADD2X2)
  #define VM 2
  #define VN 2
  #define VL 200
#elif defined(TARGET_MMM1X1)
  #define VM 1
  #define VN 1
  #define VL 200
  #define MMM 1
#elif defined(TARGET_MMM2X2)
  #define VM 2
  #define VN 2
  #define VL 400
  #define MMM 1
#else
  #error "define one of TARGET_ADD1X1 / TARGET_ADD2X2 / TARGET_MMM1X1 / TARGET_MMM2X2"
#endif

// VL must equal the chip's LANELEN == NSTEP, and the grid must match its M/N.

#ifdef MMM
  #define BATCH 3
  #define KLEN 4
  #define PROG_CYCLES 16      // when the first activation lands
#endif

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

// Non-zero values on one edge, in arrival order, up to `cap` per row.
static int collect(const half *o, int row, float *dst, int cap) {
  int n = 0;
  for (int k = 0; k < VL; k++) {
    unsigned short vb;
    memcpy(&vb, &o[row * VL + k], 2);
    if (vb != 0 && n < cap) dst[n++] = (float)o[row * VL + k];
  }
  return n;
}

// How many rows carry `want` at least once -- the add targets only care that
// each PE produced the value, not when.
static int rows_hit(const half *o, int rows, unsigned short want) {
  int n = 0;
  for (int r = 0; r < rows; r++)
    for (int k = 0; k < VL; k++) {
      unsigned short vb;
      memcpy(&vb, &o[r * VL + k], 2);
      if (vb == want) { n++; break; }
    }
  return n;
}

int main() {
  static int32_t prime_cfg[VM][VN];
  static half in_w[VM][VL], in_e[VM][VL], in_n[VN][VL], in_s[VN][VL];
  static half out_w[VM][VL], out_e[VM][VL], out_n[VN][VL], out_s[VN][VL];
  static int32_t iv_w[VM][VL], iv_e[VM][VL], iv_n[VN][VL], iv_s[VN][VL];
  static int32_t rin_w[VM][VL], rin_e[VM][VL], rin_n[VN][VL], rin_s[VN][VL];
  static int32_t rout_w[VM][VL], rout_e[VM][VL], rout_n[VN][VL], rout_s[VN][VL];

  memset(in_w, 0, sizeof in_w); memset(in_e, 0, sizeof in_e);
  memset(in_n, 0, sizeof in_n); memset(in_s, 0, sizeof in_s);
  memset(iv_w, 0, sizeof iv_w); memset(iv_e, 0, sizeof iv_e);
  memset(iv_n, 0, sizeof iv_n); memset(iv_s, 0, sizeof iv_s);
  memset(rin_w, 0, sizeof rin_w); memset(rin_e, 0, sizeof rin_e);
  memset(rin_n, 0, sizeof rin_n); memset(rin_s, 0, sizeof rin_s);
  memset(out_w, 0, sizeof out_w); memset(out_e, 0, sizeof out_e);
  memset(out_n, 0, sizeof out_n); memset(out_s, 0, sizeof out_s);
  memset(rout_w, 0, sizeof rout_w); memset(rout_e, 0, sizeof rout_e);
  memset(rout_n, 0, sizeof rout_n); memset(rout_s, 0, sizeof rout_s);

  for (int i = 0; i < VM; i++)
    for (int j = 0; j < VN; j++) prime_cfg[i][j] = 6;

#ifdef MMM
  // Activation X[b][i] enters row i from the west, one kernel iteration apart.
  #if VM == 1
  const float X[BATCH][VM] = {{2.0f}, {4.0f}, {1.0f}};
  const float W[VM][VN] = {{3.0f}};
  #else
  const float X[BATCH][VM] = {{2.0f, 4.0f}, {1.0f, 3.0f}, {5.0f, 2.0f}};
  const float W[VM][VN] = {{1.0f, 3.0f}, {5.0f, 7.0f}};
  #endif
  for (int b = 0; b < BATCH; b++)
    for (int i = 0; i < VM; i++) {
      in_w[i][PROG_CYCLES + KLEN * b] = (half)X[b][i];
      iv_w[i][PROG_CYCLES + KLEN * b] = 1;
    }
  // North accumulator seed: a valid zero every cycle.
  for (int j = 0; j < VN; j++)
    for (int k = 0; k < VL; k++) iv_n[j][k] = 1;
#endif

  top(prime_cfg,
      in_w, iv_w, in_e, iv_e, in_n, iv_n, in_s, iv_s,
      out_w, out_e, out_n, out_s,
      rin_w, rin_e, rin_n, rin_s,
      rout_w, rout_e, rout_n, rout_s);

#ifdef MMM
  // Partial sums accumulate down column j and leave on out_s[j].
  printf("---- out_s (column j = partial sums leaving the bottom) ----\n");
  int bad = 0;
  for (int j = 0; j < VN; j++) {
    float got[BATCH];
    int n = collect(&out_s[0][0], j, got, BATCH);
    printf("  col %d:", j);
    for (int b = 0; b < n; b++) printf(" %g", (double)got[b]);
    printf("   want:");
    for (int b = 0; b < BATCH; b++) {
      float want = 0;
      for (int i = 0; i < VM; i++) want += X[b][i] * W[i][j];
      printf(" %g", (double)want);
      if (b >= n || got[b] != want) bad = 1;
    }
    printf("\n");
    if (n != BATCH) bad = 1;
  }
  if (bad)
    printf("RVCHECK FAIL: matrix product did not match\n");
  else
    printf("RVCHECK PASS: %d EVA PE(s) computed X @ W from the processor's "
           "program -- every column matches numpy\n", VM * VN);

#else   // the add targets: each PE computes 1.0 + 2.0 and sends it to an edge
  const unsigned short WANT = 0x4200;    // fp16 3.0
  #if VN == 1
  // One PE, told to send east.
  int he = rows_hit(&out_e[0][0], VM, WANT);
  if (he == 1)
    printf("RVCHECK PASS: the EVA PE executed the RV32I processor's program -- "
           "out_e carries 3.0 (0x4200)\n");
  else
    printf("RVCHECK FAIL: 3.0 (0x4200) never appeared on out_e\n");
  #else
  // Column 0 sends west, column 1 east, so every PE reaches a collector.
  int hw = rows_hit(&out_w[0][0], VM, WANT);
  int he = rows_hit(&out_e[0][0], VM, WANT);
  if (hw + he == VM * VN)
    printf("RVCHECK PASS: all %d EVA PEs ran the processor's program -- "
           "3.0 on out_w x%d and out_e x%d\n", VM * VN, hw, he);
  else
    printf("RVCHECK FAIL: %d/%d PEs produced 3.0 (out_w %d, out_e %d)\n",
           hw + he, VM * VN, hw, he);
  #endif
#endif

  // Always return 0, as the chip's own tb_replay_nb.cpp does. C simulation of
  // these designs is all-zero by construction (dataflow + feedback cannot run
  // sequentially), so a nonzero exit would abort co-sim before the RTL run --
  // which is the run that actually matters. The verdict is the RVCHECK line
  // printed during the RTL phase.
  return 0;
}
