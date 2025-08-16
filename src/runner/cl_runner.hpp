#pragma once

#include <string>
#include <vector>

struct Shape {
  int m;
  int n;
  int k;
};

struct GemmParams {
  int tile_m;
  int tile_n;
  int tile_k;
  int wg_x;
  int wg_y;
  int vec_w;
  int unroll_k;
  int lds_tile;
};

struct Result {
  double ns;
  double gflops;
  double bandwidth;
  bool pass_fail;
};

int run_gemm(const Shape &shape, const GemmParams &params, int reps, Result &out);
