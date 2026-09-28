// tb_replay_golden_stream.cpp - STREAMING throughput tb for the _cosim chip.
// Injects VB back-to-back copies of the golden activation (done in the vectors) and
// checks the output edge for VB non-overlapping copies of the golden pattern (VGMAX
// vals/row). Per row: delivered/VB (losslessness), and the steady-state spacing
// between consecutive activation-outputs (out_cyc) = sustained cyc/activation.
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

static void fill(half *d, const unsigned short *b, int n){ for(int i=0;i<n;i++) memcpy(&d[i],&b[i],2); }
static inline unsigned short hb(const half *h){ unsigned short u; memcpy(&u,h,2); return u; }

int main(){
    static half    in_w[VM][VL], in_e[VM][VL], in_n[VN][VL], in_s[VN][VL];
    static int32_t iv_w[VM][VL], iv_e[VM][VL], iv_n[VN][VL], iv_s[VN][VL];
    static half    out_w[VM][VL], out_e[VM][VL], out_n[VN][VL], out_s[VN][VL];
    static int32_t out_cyc_w[VM][VL], out_cyc_e[VM][VL], out_cyc_n[VN][VL], out_cyc_s[VN][VL];
    static int32_t rin_w[VM][VL], rin_e[VM][VL], rin_n[VN][VL], rin_s[VN][VL];
    static int32_t rout_w[VM][VL], rout_e[VM][VL], rout_n[VN][VL], rout_s[VN][VL];

    fill(&in_w[0][0],&IN0[0][0],VM*VL); fill(&in_e[0][0],&IN1[0][0],VM*VL);
    fill(&in_n[0][0],&IN2[0][0],VN*VL); fill(&in_s[0][0],&IN3[0][0],VN*VL);
    memcpy(iv_w,IV0,sizeof iv_w); memcpy(iv_e,IV1,sizeof iv_e);
    memcpy(iv_n,IV2,sizeof iv_n); memcpy(iv_s,IV3,sizeof iv_s);
    memcpy(rin_w,RIN0,sizeof rin_w); memcpy(rin_e,RIN1,sizeof rin_e);
    memcpy(rin_n,RIN2,sizeof rin_n); memcpy(rin_s,RIN3,sizeof rin_s);

    top(in_w,iv_w,in_e,iv_e,in_n,iv_n,in_s,iv_s,
        out_w,out_cyc_w,out_e,out_cyc_e,out_n,out_cyc_n,out_s,out_cyc_s,
        rin_w,rin_e,rin_n,rin_s, rout_w,rout_e,rout_n,rout_s);

    half    (*out)[VL]  = (VOUT_IDX==1)? out_e : out_s;
    int32_t (*ocyc)[VL] = (VOUT_IDX==1)? out_cyc_e : out_cyc_s;
    const unsigned short (*gold)[VL] = (const unsigned short(*)[VL])((VOUT_IDX==1)? &EOUT1[0][0] : &EOUT3[0][0]);

    printf("8x8 STREAMING replay (%s) — B=%d activations, %s, %d val/activation\n",
           VECNAME, VB, (VOUT_IDX==1)?"out_e(east)":"out_s(south)", VGMAX);
    int rows_lossless=0; double rate_sum=0; int rate_n=0;
    long tot_first=1L<<60, tot_last=-1; int tot_deliv=0;
    for(int k=0;k<VN;k++){
        unsigned short g[VGMAX]; int ng=0;
        for(int t=0;t<VGMAX;t++){ g[t]=gold[k][t]; if(g[t]) ng=t+1; }
        if(ng==0){ printf("  row %d: (no golden)\n",k); rows_lossless++; continue; }
        // find VB non-overlapping golden-pattern occurrences; record each's first-value cycle
        int deliv=0; int firstc=-1,lastc=-1; long prev=-1; double gaps=0; int ngap=0;
        for(int s=0; s+ng<=VL; ){
            int ok=1; for(int t=0;t<ng;t++) if(hb(&out[k][s+t])!=g[t]){ ok=0; break; }
            if(ok){ int c=ocyc[k][s]; if(firstc<0)firstc=c; lastc=c;
                    if(prev>=0){ gaps+=(c-prev); ngap++; } prev=c;
                    deliv++; s+=ng; }
            else s++;
        }
        double cpa = ngap>0 ? gaps/ngap : 0.0;   // sustained cyc / activation
        printf("  row %d: delivered %d/%d %s  first@%d last@%d  -> %.1f cyc/activation\n",
               k, deliv, VB, deliv==VB?"LOSSLESS":"** DROPS **", firstc, lastc, cpa);
        if(deliv==VB) rows_lossless++;
        if(ngap>0){ rate_sum+=cpa; rate_n++; }
        if(deliv>0){ if(firstc<tot_first)tot_first=firstc; if(lastc>tot_last)tot_last=lastc; tot_deliv+=deliv; }
    }
    double avg = rate_n>0 ? rate_sum/rate_n : 0.0;
    printf(">> %d/%d rows LOSSLESS (all %d activations delivered bit-exact); "
           "sustained ~%.1f cyc/activation; %d total outputs over cyc %ld..%ld\n",
           rows_lossless, VN, VB, avg, tot_deliv, tot_first, tot_last);
    int clean = (rows_lossless==VN);
    printf("%s: streaming %s (B=%d, %d/%d rows lossless bit-exact)\n",
           clean?"PASS":"FAIL", VECNAME, VB, rows_lossless, VN);
    return 0;
}
