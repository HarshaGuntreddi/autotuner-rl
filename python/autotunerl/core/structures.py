"""Data structure helpers."""
from typing import List


class UnionFind:
    def __init__(self, n: int) -> None:
        self.parent = list(range(n))

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, a: int, b: int) -> None:
        self.parent[self.find(a)] = self.find(b)


class SegmentTree:
    def __init__(self, arr: List[int]):
        self.n = len(arr)
        self.tree = [0] * (2 * self.n)
        for i, v in enumerate(arr):
            self.tree[self.n + i] = v
        for i in range(self.n - 1, 0, -1):
            self.tree[i] = max(self.tree[2 * i], self.tree[2 * i + 1])

    def query(self, l: int, r: int) -> int:
        l += self.n
        r += self.n
        res = 0
        while l < r:
            if l % 2:
                res = max(res, self.tree[l])
                l += 1
            if r % 2:
                r -= 1
                res = max(res, self.tree[r])
            l //= 2
            r //= 2
        return res
