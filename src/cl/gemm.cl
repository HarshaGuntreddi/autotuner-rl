__kernel void gemm(const int M, const int N, const int K,
                   __global const float* A,
                   __global const float* B,
                   __global float* C) {
    int row = get_global_id(0);
    int col = get_global_id(1);
    if (row < M && col < N) {
        float acc = 0.0f;
        for (int k = 0; k < K; ++k) {
            acc += A[row * K + k] * B[k * N + col];
        }
        C[row * N + col] = acc;
    }
}
