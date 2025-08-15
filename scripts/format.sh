#!/usr/bin/env bash
set -e
autopep8 -i $(git ls-files '*.py')
