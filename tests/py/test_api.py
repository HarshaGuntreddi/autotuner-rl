from fastapi.testclient import TestClient

from autotunerl.api.app import app


def test_healthz():
    client = TestClient(app)
    assert client.get("/healthz").status_code == 200


def test_ops():
    client = TestClient(app)
    resp = client.get("/ops")
    assert resp.status_code == 200
    assert "gemm" in resp.json()
