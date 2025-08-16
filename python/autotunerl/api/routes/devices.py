from fastapi import APIRouter, HTTPException

router = APIRouter()

@router.post("/devices")
def register_device():
    raise HTTPException(status_code=501, detail="Not implemented")
