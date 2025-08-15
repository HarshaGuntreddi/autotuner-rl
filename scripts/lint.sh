#!/usr/bin/env bash
set -e
python -m py_compile $(git ls-files '*.py')
