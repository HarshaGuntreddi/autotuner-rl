typedef struct {
  int tile_m;
  int tile_n;
  int tile_k;
  int wg_x;
  int wg_y;
  int vec_w;
  int unroll_k;
  int lds_tile;
} gemm_params;

__kernel void gemm_kernel(__global const float *A, __global const float *B,
                          __global float *C, int M, int N, int K,
                          gemm_params params) {
  int row = get_global_id(0);
  int col = get_global_id(1);
  if (row >= M || col >= N) return;
  float acc = 0.0f;
  for (int k = 0; k < K; ++k) {
    acc += A[row * K + k] * B[k * N + col];
  }
  C[row * N + col] = acc;
}
