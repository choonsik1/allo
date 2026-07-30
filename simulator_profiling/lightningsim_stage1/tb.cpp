#include <cstdio>
#include <cstdint>
#include "kernel.h"
int main() {
  int32_t out[1] = {0};
  top(out);
  printf("checksum = %d\n", (int)out[0]);
  return 0;
}
