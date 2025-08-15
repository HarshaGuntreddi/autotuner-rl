from fastapi.testclient import TestClient

from autotunerl.api.app import app


def test_healthz():
    client = TestClient(app)
    assert client.get("/healthz").json() == {"status": "ok"}
