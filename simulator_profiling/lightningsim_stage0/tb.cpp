// Native csim testbench for the Allo blocking producer/consumer design.
//
// Replaces Allo's generated host.cpp, which is an OpenCL host program and cannot be
// compiled as a csim testbench (needs CL/cl2.hpp). LightningSim builds an instrumented
// copy of whatever is registered via `add_files -tb`, so it must call top() directly.
//
// Design: producer_0 writes i*10 for i in 0..3 into a depth-4 stream; consumer_0 drains
// it into buf0; store_res0 copies buf0 to the m_axi output. Expected: {0,10,20,30}.
#include <cstdio>
#include <cstdint>   // MUST precede kernel.h: Allo's generated
                     // kernel.h uses int32_t without including it
#include "kernel.h"

int main() {
  int32_t out[4] = {-1, -1, -1, -1};
  top(out);

  const int32_t expected[4] = {0, 10, 20, 30};
  int errors = 0;
  for (int i = 0; i < 4; i++) {
    printf("out[%d] = %d (expected %d)\n", i, (int)out[i], (int)expected[i]);
    if (out[i] != expected[i]) errors++;
  }
  printf(errors == 0 ? "PASS\n" : "FAIL: %d mismatches\n", errors);
  return errors == 0 ? 0 : 1;
}
