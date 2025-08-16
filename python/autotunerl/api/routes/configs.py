from fastapi import APIRouter, HTTPException

router = APIRouter()

@router.get("/configs/{device}/{op}/{shape}")
def get_config(device: str, op: str, shape: str):
    raise HTTPException(status_code=501, detail="Not implemented")
