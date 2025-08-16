#include "cl_runner.hpp"

#include <nlohmann/json.hpp>

#include <iostream>
#include <sstream>
#include <string>

static Shape parse_shape(const std::string &s) {
  Shape sh{};
  char ch;
  std::stringstream ss(s);
  while (ss >> ch) {
    if (ch == 'm') { ss >> ch; ss >> sh.m; }
    else if (ch == 'n') { ss >> ch; ss >> sh.n; }
    else if (ch == 'k') { ss >> ch; ss >> sh.k; }
    ss >> ch; // comma
    if (!ss) break;
  }
  return sh;
}

int main(int argc, char **argv) {
  std::string op;
  std::string shape_str;
  std::string params_json;
  int reps = 1;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "--op" && i + 1 < argc) op = argv[++i];
    else if (arg == "--shape" && i + 1 < argc) shape_str = argv[++i];
    else if (arg == "--params-json" && i + 1 < argc) params_json = argv[++i];
    else if (arg == "--reps" && i + 1 < argc) reps = std::stoi(argv[++i]);
  }
  if (op != "gemm") {
    std::cerr << "Only gemm supported in Phase A\n";
    return 1;
  }
  Shape shape = parse_shape(shape_str);
  GemmParams params{};
  if (!params_json.empty()) {
    auto j = nlohmann::json::parse(params_json);
    params.tile_m = j.value("tile_m", 8);
    params.tile_n = j.value("tile_n", 8);
    params.tile_k = j.value("tile_k", 4);
    params.wg_x = j.value("wg_x", 8);
    params.wg_y = j.value("wg_y", 1);
    params.vec_w = j.value("vec_w", 1);
    params.unroll_k = j.value("unroll_k", 1);
    params.lds_tile = j.value("lds_tile", 0);
  }
  Result res{};
  int rc = run_gemm(shape, params, reps, res);
  nlohmann::json out{{"op", op}, {"shape", {{"m", shape.m}, {"n", shape.n}, {"k", shape.k}}},
                     {"params", params_json.empty() ? nlohmann::json::object() : nlohmann::json::parse(params_json)},
                     {"ns", res.ns}, {"gflops", res.gflops}, {"bandwidth", res.bandwidth},
                     {"pass_fail", res.pass_fail}};
  std::cout << out.dump() << std::endl;
  return rc;
}
