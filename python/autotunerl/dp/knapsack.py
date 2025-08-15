"""Simple knapsack DP returning top-K items."""
from __future__ import annotations

from dataclasses import dataclass
from typing import List


@dataclass
class Item:
    value: int
    weight: int


def solve_knapsack(items: List[Item], capacity: int, k: int = 1) -> List[int]:
    dp = [0] * (capacity + 1)
    for item in items:
        for w in range(capacity, item.weight - 1, -1):
            dp[w] = max(dp[w], dp[w - item.weight] + item.value)
    return sorted(dp, reverse=True)[:k]
