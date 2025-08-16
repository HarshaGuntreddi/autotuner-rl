#include "correctness.hpp"

#include <cmath>

void gemm_reference(const std::vector<float> &A, const std::vector<float> &B,
                     std::vector<float> &C, int M, int N, int K) {
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      float acc = 0.0f;
      for (int k = 0; k < K; ++k) {
        acc += A[i * K + k] * B[k * N + j];
      }
      C[i * N + j] = acc;
    }
  }
}

bool check_close(const std::vector<float> &a, const std::vector<float> &b,
                 float atol) {
  if (a.size() != b.size()) {
    return false;
  }
  for (size_t i = 0; i < a.size(); ++i) {
    if (std::fabs(a[i] - b[i]) > atol) {
      return false;
    }
  }
  return true;
}
