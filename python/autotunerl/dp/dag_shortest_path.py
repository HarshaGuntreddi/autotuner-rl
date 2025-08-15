"""DAG shortest path using relaxation."""
from collections import defaultdict
from typing import Dict, List, Tuple

Graph = Dict[int, List[Tuple[int, int]]]


def shortest_path(g: Graph, start: int, end: int) -> int:
    dist: Dict[int, int] = defaultdict(lambda: float('inf'))
    dist[start] = 0
    for u in sorted(g):
        for v, w in g.get(u, []):
            if dist[v] > dist[u] + w:
                dist[v] = dist[u] + w
    return int(dist[end])
