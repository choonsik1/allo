// tb_replay_fft.cpp - RTL-cosim TB for the 8x8 golden FFT replay. Programs the mesh
// from the South router (RIN3), injects the 16 FFT inputs from the West (2/row at
// VPC/VPC+1), and compares the EAST collector out_e vs the golden sys_tx_rgt pair
// (EOUT1[j][0..1]). Uses a per-row VALID WINDOW: pipeline fill can offset the first
// outputs, so we locate the golden pair as a consecutive run rather than assuming
// it lands at index 0.  Plain 20-port top().  -DVECHDR="vectors_fft_*.h"
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "hls_half.h"
#include VECHDR

void top(half in_w[VM][VL], int32_t iv_w[VM][VL], half in_e[VM][VL], int32_t iv_e[VM][VL],
         half in_n[VN][VL], int32_t iv_n[VN][VL], half in_s[VN][VL], int32_t iv_s[VN][VL],
         half out_w[VM][VL], half out_e[VM][VL], half out_n[VN][VL], half out_s[VN][VL],
         int32_t rin_w[VM][VL], int32_t rin_e[VM][VL], int32_t rin_n[VN][VL], int32_t rin_s[VN][VL],
         int32_t rout_w[VM][VL], int32_t rout_e[VM][VL], int32_t rout_n[VN][VL], int32_t rout_s[VN][VL]);

static void fill(half *d, const unsigned short *b, int n){ for(int i=0;i<n;i++) memcpy(&d[i],&b[i],2); }
static unsigned short hb(const half *h){ unsigned short u; memcpy(&u,h,2); return u; }

int main(){
    static half in_w[VM][VL],in_e[VM][VL],in_n[VN][VL],in_s[VN][VL];
    static int32_t iv_w[VM][VL],iv_e[VM][VL],iv_n[VN][VL],iv_s[VN][VL];
    static half out_w[VM][VL],out_e[VM][VL],out_n[VN][VL],out_s[VN][VL];
    static int32_t rin_w[VM][VL],rin_e[VM][VL],rin_n[VN][VL],rin_s[VN][VL];
    static int32_t rout_w[VM][VL],rout_e[VM][VL],rout_n[VN][VL],rout_s[VN][VL];

    fill(&in_w[0][0],&IN0[0][0],VM*VL); fill(&in_e[0][0],&IN1[0][0],VM*VL);
    fill(&in_n[0][0],&IN2[0][0],VN*VL); fill(&in_s[0][0],&IN3[0][0],VN*VL);
    memcpy(iv_w,IV0,sizeof iv_w); memcpy(iv_e,IV1,sizeof iv_e);
    memcpy(iv_n,IV2,sizeof iv_n); memcpy(iv_s,IV3,sizeof iv_s);
    memcpy(rin_w,RIN0,sizeof rin_w); memcpy(rin_e,RIN1,sizeof rin_e);
    memcpy(rin_n,RIN2,sizeof rin_n); memcpy(rin_s,RIN3,sizeof rin_s);

    top(in_w,iv_w,in_e,iv_e,in_n,iv_n,in_s,iv_s,
        out_w,out_e,out_n,out_s,
        rin_w,rin_e,rin_n,rin_s, rout_w,rout_e,rout_n,rout_s);

    // ---- per-row VALID WINDOW: find the golden pair (g0,g1) as a consecutive run ----
    printf("8x8 golden FFT replay (%s) — EAST edge out_e vs golden sys_tx_rgt\n", VECNAME);
    int rows_ok = 0;
    for (int j = 0; j < VN; j++) {
        unsigned short g0 = EOUT1[j][0], g1 = EOUT1[j][1];
        // gather the non-zero out_e run for this row
        int found = -1;
        for (int k = 0; k + 1 < VL; k++) {
            if (hb(&out_e[j][k]) == g0 && hb(&out_e[j][k+1]) == g1) { found = k; break; }
        }
        // also collect first few non-zero for the print
        char seen[128] = ""; int p = 0, cnt = 0;
        for (int k = 0; k < VL && cnt < 6; k++) { unsigned short v = hb(&out_e[j][k]); if (v) { p += snprintf(seen+p, sizeof(seen)-p, "%04x ", v); cnt++; } }
        if (found >= 0) { rows_ok++;
            printf("  row %d: OK  golden %04x %04x found @slot %d,%d   (out_e nz: %s)\n", j, g0, g1, found, found+1, seen);
        } else {
            printf("  row %d: x   golden %04x %04x NOT found         (out_e nz: %s)\n", j, g0, g1, seen);
        }
    }
    int clean = (rows_ok == VN);
    printf("%s: FFT 8x8 cosim (%d/%d rows bit-exact vs golden)\n", clean ? "PASS" : "FAIL", rows_ok, VN);
    return 0;
}
