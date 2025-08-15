"""CRUD helpers."""
from sqlalchemy.orm import Session

from . import models


def get_or_create_device(db: Session, fingerprint: str, name: str) -> models.Device:
    device = db.query(models.Device).filter_by(fingerprint=fingerprint).first()
    if not device:
        device = models.Device(fingerprint=fingerprint, name=name)
        db.add(device)
        db.commit()
        db.refresh(device)
    return device
