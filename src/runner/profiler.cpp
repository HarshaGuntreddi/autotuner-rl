#include "profiler.hpp"

double event_duration_ns(cl_event event) {
  cl_ulong start = 0, end = 0;
  clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(start), &start, nullptr);
  clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(end), &end, nullptr);
  return static_cast<double>(end - start);
}
