#include "cl_runner.hpp"
#include "correctness.hpp"
#include <cassert>
#include <vector>

int main() {
    int M = 2, N = 2, K = 2;
    std::vector<float> A = {1, 2, 3, 4};
    std::vector<float> B = {5, 6, 7, 8};
    std::vector<float> C(4);
    auto res = runner::run_gemm("src/cl/gemm.cl", A, B, C, M, N, K);
    (void)res;
    bool ok = runner::check_gemm(A, B, C, M, N, K);
    assert(ok);
    return 0;
}
