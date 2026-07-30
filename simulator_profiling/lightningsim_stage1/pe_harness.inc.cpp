// Stage 1 harness: wrap the PE so NO hls::stream appears in the top-level signature.
// Top-level stream ports make Vitis emit streamcpy_hls glue calling fpga_fifo_*_N,
// which LightningSim's runtime does not provide (it models top ports via _autotb_Fifo*).
// Keeping streams internal matches the shape that works (Stage 0).
//===----------------------------------------------------------------------===//
#define PE_T 336

static void pe_feed(
  hls::stream< ap_uint<26> >& a0, hls::stream< ap_uint<26> >& a1,
  hls::stream< ap_uint<26> >& a2, hls::stream< ap_uint<26> >& a3,
  hls::stream< int32_t >& b0, hls::stream< int32_t >& b1,
  hls::stream< int32_t >& b2, hls::stream< int32_t >& b3,
  hls::stream< ap_uint<17> >& c0, hls::stream< ap_uint<17> >& c1,
  hls::stream< ap_uint<17> >& c2, hls::stream< ap_uint<17> >& c3
) {
  for (int k = 0; k < PE_T; k++) {
  #pragma HLS pipeline II=1
    ap_uint<26> a = (ap_uint<26>)((k * 2654435761u) & 0x3FFFFFF);
    ap_uint<17> c = (ap_uint<17>)((k * 40503u) & 0x1FFFF);
    a0.write(a); a1.write(a + 1); a2.write(a + 2); a3.write(a + 3);
    b0.write(k); b1.write(k + 1); b2.write(k + 2); b3.write(k + 3);
    c0.write(c); c1.write(c + 1); c2.write(c + 2); c3.write(c + 3);
  }
}

static void pe_drain(
  hls::stream< ap_uint<26> >& a0, hls::stream< ap_uint<26> >& a1,
  hls::stream< ap_uint<26> >& a2, hls::stream< ap_uint<26> >& a3,
  hls::stream< ap_uint<17> >& b0, hls::stream< ap_uint<17> >& b1,
  hls::stream< ap_uint<17> >& b2, hls::stream< ap_uint<17> >& b3,
  hls::stream< int32_t >& c0, hls::stream< int32_t >& c1,
  hls::stream< int32_t >& c2, hls::stream< int32_t >& c3,
  int32_t *out
) {
  int32_t s = 0;
  for (int k = 0; k < PE_T + 1; k++) {   // +1: node_0_0 writes each output once
  #pragma HLS pipeline II=1              // before the t-loop, then once per iteration
    s += (int32_t)a0.read() + (int32_t)a1.read() + (int32_t)a2.read() + (int32_t)a3.read();
    s += (int32_t)b0.read() + (int32_t)b1.read() + (int32_t)b2.read() + (int32_t)b3.read();
    s += c0.read() + c1.read() + c2.read() + c3.read();
  }
  out[0] = s;
}

extern "C" {
void top(int32_t *out) {
  #pragma HLS interface m_axi port=out offset=slave bundle=gmem0
  #pragma HLS dataflow
  hls::stream< ap_uint<26> > q0, q1, q2, q3, i12, i13, i14, i15;
  hls::stream< ap_uint<17> > q4, q5, q6, q7, i20, i21, i22, i23;
  hls::stream< int32_t >     q8, q9, q10, q11, i16, i17, i18, i19;
  pe_feed(i12, i13, i14, i15, i16, i17, i18, i19, i20, i21, i22, i23);
  node_0_0(q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11,
           i12, i13, i14, i15, i16, i17, i18, i19, i20, i21, i22, i23);
  pe_drain(q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, out);
}
}
