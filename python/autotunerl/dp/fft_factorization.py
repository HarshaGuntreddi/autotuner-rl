"""Placeholder for FFT factorization DP."""
from __future__ import annotations

from typing import List


def factorize(n: int) -> List[int]:
    factors: List[int] = []
    f = 2
    while n > 1:
        while n % f == 0:
            factors.append(f)
            n //= f
        f += 1
    return factors
