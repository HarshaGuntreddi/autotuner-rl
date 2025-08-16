from fastapi import FastAPI

app = FastAPI(title="AutoTunerRL++")

@app.get("/healthz")
def healthz():
    return {"status": "ok"}

@app.get("/ops")
def list_ops():
    return ["gemm", "fft1d", "fft2d", "reduce", "scan", "conv2d"]
