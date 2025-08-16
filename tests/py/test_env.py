from autotunerl.rl.env import DummyEnv


def test_env_reset():
    env = DummyEnv()
    assert env.reset() == 0
