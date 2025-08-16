#include "cl_runner.hpp"
#include "correctness.hpp"
#include "profiler.hpp"

#include <CL/cl.h>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

namespace {
std::string read_file(const std::string &path) {
  std::ifstream ifs(path);
  return std::string((std::istreambuf_iterator<char>(ifs)),
                     std::istreambuf_iterator<char>());
}
}

int run_gemm(const Shape &shape, const GemmParams &params, int reps,
             Result &out) {
  cl_int err;
  cl_platform_id platform = nullptr;
  cl_device_id device = nullptr;
  cl_uint num_platforms = 0;
  err = clGetPlatformIDs(1, &platform, &num_platforms);
  if (err != CL_SUCCESS || num_platforms == 0) {
    std::cerr << "No OpenCL platform\n";
    return 1;
  }
  err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_DEFAULT, 1, &device, nullptr);
  if (err != CL_SUCCESS) {
    std::cerr << "No OpenCL device\n";
    return 1;
  }

  cl_context context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &err);
  if (err != CL_SUCCESS) {
    std::cerr << "Failed to create context\n";
    return 1;
  }
  cl_command_queue queue =
      clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &err);
  if (err != CL_SUCCESS) {
    std::cerr << "Failed to create queue\n";
    clReleaseContext(context);
    return 1;
  }

  std::string src = read_file("src/cl/gemm.cl");
  const char *src_c = src.c_str();
  size_t src_len = src.size();
  cl_program program =
      clCreateProgramWithSource(context, 1, &src_c, &src_len, &err);
  if (err != CL_SUCCESS) {
    std::cerr << "Failed to create program\n";
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    return 1;
  }
  err = clBuildProgram(program, 1, &device, "-cl-std=CL1.2", nullptr, nullptr);
  if (err != CL_SUCCESS) {
    size_t log_size = 0;
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, nullptr,
                          &log_size);
    std::string log(log_size, '\0');
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size,
                          &log[0], nullptr);
    std::cerr << log << "\n";
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    return 2;
  }

  cl_kernel kernel = clCreateKernel(program, "gemm_kernel", &err);
  if (err != CL_SUCCESS) {
    std::cerr << "Failed to create kernel\n";
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    return 1;
  }

  size_t M = shape.m, N = shape.n, K = shape.k;
  std::vector<float> A(M * K), B(K * N), C(M * N), C_ref(M * N);
  std::mt19937 rng(1337);
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  for (auto &v : A) v = dist(rng);
  for (auto &v : B) v = dist(rng);

  cl_mem bufA = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                               sizeof(float) * A.size(), A.data(), &err);
  cl_mem bufB = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                               sizeof(float) * B.size(), B.data(), &err);
  cl_mem bufC = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                               sizeof(float) * C.size(), nullptr, &err);

  clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufA);
  clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufB);
  clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufC);
  clSetKernelArg(kernel, 3, sizeof(int), &M);
  clSetKernelArg(kernel, 4, sizeof(int), &N);
  clSetKernelArg(kernel, 5, sizeof(int), &K);
  clSetKernelArg(kernel, 6, sizeof(GemmParams), &params);

  size_t global[2] = {M, N};
  size_t local[2] = {static_cast<size_t>(params.wg_x),
                     static_cast<size_t>(params.wg_y)};

  // ensure local sizes are valid
  size_t max_wg = 0;
  clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &max_wg,
                  nullptr);
  if (local[0] * local[1] > max_wg) {
    local[0] = 1;
    local[1] = 1;
  }

  // warmup
  clEnqueueNDRangeKernel(queue, kernel, 2, nullptr, global, local, 0, nullptr,
                         nullptr);
  clFinish(queue);

  double total_ns = 0.0;
  for (int i = 0; i < reps; ++i) {
    cl_event evt;
    clEnqueueNDRangeKernel(queue, kernel, 2, nullptr, global, local, 0, nullptr,
                           &evt);
    clWaitForEvents(1, &evt);
    total_ns += event_duration_ns(evt);
    clReleaseEvent(evt);
  }

  clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0, sizeof(float) * C.size(),
                      C.data(), 0, nullptr, nullptr);

  gemm_reference(A, B, C_ref, M, N, K);
  bool pass = check_close(C, C_ref);

  double avg_ns = total_ns / reps;
  double flops = 2.0 * M * N * K;
  out.ns = avg_ns;
  out.gflops = flops / avg_ns / 1e6;
  out.bandwidth = 0.0; // placeholder
  out.pass_fail = pass;

  clReleaseMemObject(bufA);
  clReleaseMemObject(bufB);
  clReleaseMemObject(bufC);
  clReleaseKernel(kernel);
  clReleaseProgram(program);
  clReleaseCommandQueue(queue);
  clReleaseContext(context);
  return pass ? 0 : 3;
}
