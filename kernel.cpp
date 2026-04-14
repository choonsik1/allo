
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

void load_buf0(
  int32_t v0[16],
  int32_t v1[4][4]
) {	//
  #pragma HLS array_partition variable=v1 complete dim=1
  #pragma HLS array_partition variable=v1 complete dim=2

  l_S_load_buf0_load_buf0_l_0: for (int load_buf0_l_0 = 0; load_buf0_l_0 < 4; load_buf0_l_0++) {	//
    l_load_buf0_l_1: for (int load_buf0_l_1 = 0; load_buf0_l_1 < 4; load_buf0_l_1++) {	//
    #pragma HLS pipeline II=1 rewind
      int32_t v4 = v0[((load_buf0_l_0 * 4) + load_buf0_l_1)];	//
      v1[load_buf0_l_0][load_buf0_l_1] = v4;	//
    }
  }
}

void load_buf1(
  int32_t v5[16],
  int32_t v6[4][4]
) {	//
  #pragma HLS array_partition variable=v6 complete dim=1
  #pragma HLS array_partition variable=v6 complete dim=2

  l_S_load_buf1_load_buf1_l_0: for (int load_buf1_l_0 = 0; load_buf1_l_0 < 4; load_buf1_l_0++) {	//
    l_load_buf1_l_1: for (int load_buf1_l_1 = 0; load_buf1_l_1 < 4; load_buf1_l_1++) {	//
    #pragma HLS pipeline II=1 rewind
      int32_t v9 = v5[((load_buf1_l_0 * 4) + load_buf1_l_1)];	//
      v6[load_buf1_l_0][load_buf1_l_1] = v9;	//
    }
  }
}

void store_res2(
  int32_t v10[4][4],
  int32_t v11[16]
) {	//
  #pragma HLS array_partition variable=v10 complete dim=1
  #pragma HLS array_partition variable=v10 complete dim=2

  l_S_store_res2_store_res2_l_0: for (int store_res2_l_0 = 0; store_res2_l_0 < 4; store_res2_l_0++) {	//
    l_store_res2_l_1: for (int store_res2_l_1 = 0; store_res2_l_1 < 4; store_res2_l_1++) {	//
    #pragma HLS pipeline II=1 rewind
      int32_t v14 = v10[store_res2_l_0][store_res2_l_1];	//
      v11[((store_res2_l_0 * 4) + store_res2_l_1)] = v14;	//
    }
  }
}

/// This is top function.
void matmul_outer(
  int32_t *v15,
  int32_t *v16,
  int32_t *v17
) {	// L3
  #pragma HLS interface m_axi port=v15 offset=slave bundle=gmem0
  #pragma HLS interface m_axi port=v16 offset=slave bundle=gmem1
  #pragma HLS interface m_axi port=v17 offset=slave bundle=gmem2
  int32_t buf0[4][4];	//
  #pragma HLS array_partition variable=buf0 complete dim=1
  #pragma HLS array_partition variable=buf0 complete dim=2

  load_buf0(v15, buf0);	//
  int32_t buf1[4][4];	//
  #pragma HLS array_partition variable=buf1 complete dim=1
  #pragma HLS array_partition variable=buf1 complete dim=2

  load_buf1(v16, buf1);	//
  int32_t C[4][4];	// L4
  #pragma HLS array_partition variable=C complete dim=1
  #pragma HLS array_partition variable=C complete dim=2

  for (int v21 = 0; v21 < 4; v21++) {	// L6
    for (int v22 = 0; v22 < 4; v22++) {	// L6
      C[v21][v22] = 0;	// L6
    }
  }
  l_S_k_0_k: for (int k = 0; k < 4; k++) {	// L7
  #pragma HLS pipeline II=1
    l_S_l_0_l: for (int l = 0; l < 4; l++) {	// L8
      int32_t v25 = buf0[l][k];	// L9
      int32_t a_val;	// L10
      a_val = v25;	// L11
      l_S_m_0_m: for (int m = 0; m < 4; m++) {	// L12
        int32_t v28 = a_val;	// L13
        int32_t v29 = buf1[k][m];	// L14
        int64_t v30 = v28;	// L15
        int64_t v31 = v29;	// L16
        int64_t v32 = v30 * v31;	// L17
        int32_t v33 = C[l][m];	// L18
        ap_int<65> v34 = v33;	// L19
        ap_int<65> v35 = v32;	// L20
        ap_int<65> v36 = v34 + v35;	// L21
        int32_t v37 = v36;	// L22
        C[l][m] = v37;	// L23
      }
    }
  }
  store_res2(C, v17);	//
}


} // extern "C"
