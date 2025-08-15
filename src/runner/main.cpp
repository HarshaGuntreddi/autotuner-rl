#include "cl_runner.hpp"
#include "correctness.hpp"
#include <iostream>
#include <vector>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "usage: runner <kernel.cl>" << std::endl;
        return 1;
    }
    int M = 16, N = 16, K = 16;
    std::vector<float> A(M * K, 1.0f), B(K * N, 1.0f), C(M * N, 0.0f);
    auto res = runner::run_gemm(argv[1], A, B, C, M, N, K);
    std::cout << "{\"ns\":" << res.ns
              << ",\"gflops\":" << res.gflops
              << ",\"bandwidth\":" << res.bandwidth
              << ",\"pass\":" << (res.pass_fail ? "true" : "false")
              << "}" << std::endl;
    return 0;
}
