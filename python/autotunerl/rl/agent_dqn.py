"""Very small DQN-like loop stub."""
from __future__ import annotations

from typing import Callable

import random

from . import env


def train(policy: Callable[[env.State], int], episodes: int = 1) -> None:
    for _ in range(episodes):
        state = env.reset()
        done = False
        while not done:
            action = policy(state)
            state, reward, done, _ = env.step(state, action)
            _ = reward


def random_policy(_: env.State) -> int:
    return random.randint(0, 1)
