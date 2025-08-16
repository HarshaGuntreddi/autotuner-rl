# AutoTunerRL++

AutoTunerRL++ is a prototype auto-tuner for OpenCL kernels combining dynamic programming and reinforcement learning.

```
+------------+      +-----------+      +-------+
| CLI/REST  | ---> | C++ Runner| ---> | Redis |
+------------+      +-----------+      +-------+
        |                                   |
        v                                   v
   PostgreSQL                           TorchRL
```

## Quickstart

```bash
# Install system dependencies
bash scripts/setup_pocl.sh

# Build C++ runner
rm -rf build && mkdir build && cd build && cmake -GNinja -DCMAKE_BUILD_TYPE=Release .. && ninja && ctest -V

# Run a tiny GEMM benchmark
./autotunerl_runner --op gemm --shape m=128,n=128,k=128 \
  --params-json '{"tile_m":8,"tile_n":8,"tile_k":4,"wg_x":8,"wg_y":1,"vec_w":1,"unroll_k":1,"lds_tile":0}' \
  --reps 2 | jq .

# Install Python package
cd .. && pip install -e . && autotunerl --help
```

## Troubleshooting

- **OpenCL not found**: ensure `pocl-opencl-icd` and `ocl-icd-opencl-dev` are installed.
- **Linker errors**: verify `libOpenCL.so` exists in `/usr/lib/x86_64-linux-gnu`.
- **POCL missing**: run `sudo apt-get install pocl-opencl-icd`.
