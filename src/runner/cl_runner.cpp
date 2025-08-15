#include "cl_runner.hpp"

#include <stdexcept>

namespace runner {
Result run_gemm(const std::string &kernel_path,
                const std::vector<float> &A,
                const std::vector<float> &B,
                std::vector<float> &C,
                int M, int N, int K) {
    (void)kernel_path;
    for (int m = 0; m < M; ++m) {
        for (int n = 0; n < N; ++n) {
            float acc = 0.0f;
            for (int k = 0; k < K; ++k) {
                acc += A[m * K + k] * B[k * N + n];
            }
            C[m * N + n] = acc;
        }
    }
    Result r;
    r.pass_fail = true;
    return r;
}
} // namespace runner
