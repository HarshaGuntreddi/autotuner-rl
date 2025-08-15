#include "correctness.hpp"

namespace runner {
bool check_gemm(const std::vector<float> &A,
                const std::vector<float> &B,
                const std::vector<float> &C,
                int M, int N, int K, float tol) {
    for (int m = 0; m < M; ++m) {
        for (int n = 0; n < N; ++n) {
            float ref = 0.0f;
            for (int k = 0; k < K; ++k) {
                ref += A[m * K + k] * B[k * N + n];
            }
            if (std::abs(ref - C[m * N + n]) > tol) {
                return false;
            }
        }
    }
    return true;
}
} // namespace runner
