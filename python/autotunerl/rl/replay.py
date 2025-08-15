"""Simple replay buffer."""
from collections import deque
from typing import Deque, Tuple

Transition = Tuple[int, float]


class ReplayBuffer:
    def __init__(self, capacity: int = 100) -> None:
        self.buffer: Deque[Transition] = deque(maxlen=capacity)

    def add(self, transition: Transition) -> None:
        self.buffer.append(transition)

    def sample(self, n: int) -> list[Transition]:
        return list(self.buffer)[:n]
