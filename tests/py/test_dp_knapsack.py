from autotunerl.dp.knapsack import Item, solve_knapsack


def test_knapsack_basic():
    items = [Item(3, 2), Item(4, 3)]
    assert solve_knapsack(items, 3)[0] == 4
