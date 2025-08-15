cmake_minimum_required(VERSION 3.16)
project(autotunerl_runner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(OpenCL REQUIRED)

add_executable(autotunerl_runner
    src/runner/main.cpp
    src/runner/cl_runner.cpp
    src/runner/correctness.cpp
    src/runner/profiler.cpp)

target_include_directories(autotunerl_runner PRIVATE src/runner ${OpenCL_INCLUDE_DIRS})
target_link_libraries(autotunerl_runner PRIVATE ${OpenCL_LIBRARIES})

enable_testing()
add_subdirectory(tests/cpp)
