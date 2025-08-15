#!/usr/bin/env bash
set -e
python -m autotunerl.cli bench --suite gemm-scaling
