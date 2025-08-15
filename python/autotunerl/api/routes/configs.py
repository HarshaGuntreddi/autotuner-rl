from fastapi import APIRouter

router = APIRouter(prefix="/configs")


@router.get("/{device}/{op}")
def get_config(device: str, op: str) -> dict[str, str]:
    return {"device": device, "op": op}
