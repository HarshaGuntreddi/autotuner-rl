from fastapi import FastAPI

app = FastAPI(title="AutoTunerRL API")


@app.get("/healthz")
def healthz() -> dict[str, str]:
    return {"status": "ok"}


@app.get("/ops")
def list_ops() -> list[str]:
    return ["gemm", "fft1d"]
