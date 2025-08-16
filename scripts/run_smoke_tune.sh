#!/usr/bin/env bash
set -e
python -m autotunerl.cli tune --op gemm --m 128 --n 128 --k 128 --reps 1
