from fastapi import APIRouter

router = APIRouter(prefix="/devices")


@router.post("")
def register_device() -> dict[str, str]:
    return {"device_id": "dev0"}
