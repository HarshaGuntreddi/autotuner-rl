#include "cl_runner.hpp"
#include "correctness.hpp"

#include <cassert>
#include <vector>

int main() {
  Shape shape{2, 2, 2};
  GemmParams p{8,8,4,8,1,1,1,0};
  Result r{};
  int rc = run_gemm(shape, p, 1, r);
  assert(rc == 0);
  assert(r.pass_fail);
  return 0;
}
