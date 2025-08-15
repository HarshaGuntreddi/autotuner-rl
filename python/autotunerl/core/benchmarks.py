"""Benchmark helpers."""
from typing import List, Dict


def list_suites() -> List[str]:
    return ["gemm-scaling"]


def get_suite(name: str) -> Dict[str, object]:
    return {"name": name}
