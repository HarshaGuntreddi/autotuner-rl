from autotunerl.rl import env


def test_env_runs():
    state = env.reset()
    next_state, reward, done, _ = env.step(state, 0)
    assert isinstance(next_state, env.State)
    assert isinstance(reward, float)
    assert isinstance(done, bool)
