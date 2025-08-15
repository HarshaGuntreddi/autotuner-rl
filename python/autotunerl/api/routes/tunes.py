from fastapi import APIRouter

router = APIRouter(prefix="/tunes")


@router.post("")
def submit_tune() -> dict[str, str]:
    return {"tune_id": "tune0"}
