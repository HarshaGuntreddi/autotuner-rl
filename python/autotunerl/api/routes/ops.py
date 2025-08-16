from fastapi import APIRouter

router = APIRouter()

@router.get("/ops")
def list_ops():
    return ["gemm", "fft1d", "fft2d", "reduce", "scan", "conv2d"]
