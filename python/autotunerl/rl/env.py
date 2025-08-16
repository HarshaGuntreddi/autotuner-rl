class DummyEnv:
    def reset(self):
        return 0

    def step(self, action):
        return 0, 0.0, True, {}
