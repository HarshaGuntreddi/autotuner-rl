cmake_minimum_required(VERSION 3.16)
project(autotunerl LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(OpenCL REQUIRED)

add_compile_options(-O3 -DNDEBUG -DCL_TARGET_OPENCL_VERSION=120)

add_executable(autotunerl_runner
  src/runner/main.cpp
  src/runner/cl_runner.cpp
  src/runner/correctness.cpp
  src/runner/profiler.cpp
)
target_include_directories(autotunerl_runner PRIVATE src/runner)
target_link_libraries(autotunerl_runner OpenCL::OpenCL)

add_executable(autotunerl_tests
  tests/cpp/test_correctness.cpp
  src/runner/cl_runner.cpp
  src/runner/correctness.cpp
  src/runner/profiler.cpp
)
target_include_directories(autotunerl_tests PRIVATE src/runner)
target_link_libraries(autotunerl_tests OpenCL::OpenCL)

enable_testing()
add_test(NAME autotunerl_tests COMMAND autotunerl_tests)
