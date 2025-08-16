from fastapi import APIRouter, HTTPException

router = APIRouter()

@router.post("/tunes")
def create_tune():
    raise HTTPException(status_code=501, detail="Not implemented")
