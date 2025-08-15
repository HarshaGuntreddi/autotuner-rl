#pragma once

#include <vector>

namespace runner {
bool check_gemm(const std::vector<float> &A,
                const std::vector<float> &B,
                const std::vector<float> &C,
                int M, int N, int K, float tol = 1e-3f);
}
