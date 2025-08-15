#pragma once

#include <chrono>

namespace runner {
class Timer {
public:
    void start() { begin = std::chrono::high_resolution_clock::now(); }
    double stop() {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::nano>(end - begin).count();
    }

private:
    std::chrono::high_resolution_clock::time_point begin;
};
} // namespace runner
