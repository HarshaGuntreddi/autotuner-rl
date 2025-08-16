class ReplayBuffer:
    def __init__(self):
        self.data = []

    def add(self, item):
        self.data.append(item)
