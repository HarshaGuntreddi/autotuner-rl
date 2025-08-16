#pragma once

#include <vector>

void gemm_reference(const std::vector<float> &A, const std::vector<float> &B,
                     std::vector<float> &C, int M, int N, int K);

bool check_close(const std::vector<float> &a, const std::vector<float> &b,
                 float atol = 1e-5f);
