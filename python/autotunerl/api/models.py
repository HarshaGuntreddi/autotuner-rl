from pydantic import BaseModel, Field
from typing import Dict, Literal


class DeviceCreate(BaseModel):
    fingerprint: str
    name: str


class TuneRequest(BaseModel):
    device_id: str
    op: Literal['gemm', 'fft1d']
    shape: Dict[str, int]
    budget_minutes: int = Field(gt=0, le=240)
    strategy: Dict[str, bool]
