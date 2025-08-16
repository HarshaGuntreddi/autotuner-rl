#!/usr/bin/env bash
set -e
python -m autotunerl.cli tune --op gemm --m 256 --n 256 --k 256 --reps 3
