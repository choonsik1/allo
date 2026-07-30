
//===------------------------------------------------------------*- C++ -*-===//
//
// Automatically generated file for High-level Synthesis (HLS).
//
//===----------------------------------------------------------------------===//
#include <algorithm>
#include <ap_axi_sdata.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>
#include <hls_vector.h>
#include <math.h>
#include <stdint.h>
using namespace std;

extern "C" {

void producer_0(
  hls::stream< int32_t >& v0
) {	// L2
  l_S_i_0_i: for (int i = 0; i < 4; i++) {	// L4
    int64_t v2 = i;	// L5
    int64_t v3 = v2 * 10;	// L6
    int32_t v4 = v3;	// L7
    int32_t x;	// L8
    x = v4;	// L9
    int32_t v6 = x;	// L10
    v0.write(v6);	// L11
  }
}

void consumer_0(
  int32_t v7[4],
  hls::stream< int32_t >& v8
) {	// L15
  l_S_i_0_i1: for (int i1 = 0; i1 < 4; i1++) {	// L16
    int32_t v10 = v8.read();	// L17
    int32_t v;	// L18
    v = v10;	// L19
    int32_t v12 = v;	// L20
    v7[i1] = v12;	// L21
  }
}

void store_res0(
  int32_t v13[4],
  int32_t v14[4]
) {	//
  l_S_store_res0_store_res0_l_0: for (int store_res0_l_0 = 0; store_res0_l_0 < 4; store_res0_l_0++) {	//
  #pragma HLS pipeline II=1
    int32_t v16 = v13[store_res0_l_0];	//
    v14[store_res0_l_0] = v16;	//
  }
}

/// This is top function.
void top(
  int32_t *v17
) {	// L25
  #pragma HLS interface m_axi port=v17 offset=slave bundle=gmem0
  #pragma HLS dataflow
  int32_t buf0[4];	//
  hls::stream< int32_t > v19;
  #pragma HLS stream variable=v19 depth=4	// L26
  producer_0(v19);	// L27
  consumer_0(buf0, v19);	// L28
  store_res0(buf0, v17);	//
}


} // extern "C"
