from .models import Device


def get_device(session, name: str):
    return session.query(Device).filter_by(name=name).first()
