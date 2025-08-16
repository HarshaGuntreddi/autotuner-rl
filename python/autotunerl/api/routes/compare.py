from fastapi import APIRouter, HTTPException

router = APIRouter()

@router.post("/benchmarks/compare")
def compare_runs():
    raise HTTPException(status_code=501, detail="Not implemented")
