#!/usr/bin/env bash
set -e
sudo apt-get update
sudo apt-get install -y build-essential cmake ninja-build ocl-icd-opencl-dev pocl-opencl-icd nlohmann-json3-dev python3-pip python3.11-venv
