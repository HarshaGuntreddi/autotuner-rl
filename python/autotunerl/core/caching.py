"""Simple LRU cache."""
from functools import lru_cache


@lru_cache(maxsize=128)
def expensive(x: int) -> int:
    return x * x
