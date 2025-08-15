#pragma once

#include <CL/cl.h>
#include <string>
#include <vector>

namespace runner {
struct Result {
    double ns{0};
    double gflops{0};
    double bandwidth{0};
    bool pass_fail{false};
};

Result run_gemm(const std::string &kernel_path,
                const std::vector<float> &A,
                const std::vector<float> &B,
                std::vector<float> &C,
                int M, int N, int K);
} // namespace runner
