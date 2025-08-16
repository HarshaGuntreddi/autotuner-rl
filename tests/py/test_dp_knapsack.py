from autotunerl.dp.knapsack import solve_knapsack


def test_knapsack_placeholder():
    assert solve_knapsack([], 0) == []
