"""Minimal RL environment stub."""
from __future__ import annotations

from dataclasses import dataclass
from typing import Dict, Tuple


@dataclass
class State:
    step: int = 0


def reset() -> State:
    return State()


def step(state: State, action: int) -> Tuple[State, float, bool, Dict[str, float]]:
    next_state = State(step=state.step + 1)
    reward = 1.0 if action == 0 else 0.0
    done = next_state.step >= 10
    return next_state, reward, done, {}
