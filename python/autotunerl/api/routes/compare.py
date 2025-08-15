from fastapi import APIRouter

router = APIRouter(prefix="/benchmarks")


@router.post("/compare")
def compare() -> dict[str, int]:
    return {"diff": 0}
