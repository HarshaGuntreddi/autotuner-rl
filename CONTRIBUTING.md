# Contributing

Thank you for your interest in contributing to AutoTunerRL++! Please fork the repository and submit pull requests.

## Development Setup

1. Run `scripts/setup_pocl.sh` to install dependencies.
2. Create a Python virtual environment and install the package with `pip install -e .`.
3. Build the C++ runner with CMake and Ninja.

## Commit Guidelines

- Use clear, conventional commit messages.
- Include tests for new features.
- Ensure `ctest` and `pytest` pass before submitting a PR.
