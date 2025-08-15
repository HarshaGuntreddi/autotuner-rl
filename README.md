# AutoTunerRL++

AutoTunerRL++ is an experimental framework for tuning OpenCL kernels using
dynamic programming and reinforcement learning. It exposes a C++ runner with
OpenCL kernels, a Python package with planners and an RL agent, and a REST API
for orchestrating tuning jobs.

## Quickstart

```bash
# Build C++ runner
mkdir -p build && cd build && cmake .. && make -j

# Run Python tests
pip install -e .
pytest -q
```

## Environment Variables

See `.env.example` for configuration flags used by the API and workers.

## Troubleshooting

* Ensure OpenCL headers and the POCL CPU runtime are installed.
* Use `clinfo` to confirm that an OpenCL platform is available.
