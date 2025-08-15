from fastapi import APIRouter

router = APIRouter(prefix="/ops")


@router.get("")
def list_ops() -> list[str]:
    return ["gemm", "fft1d"]
