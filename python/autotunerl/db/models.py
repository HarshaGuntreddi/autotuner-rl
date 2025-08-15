"""Minimal ORM models."""
from sqlalchemy import Column, Integer, String

from .base import Base


class Device(Base):
    __tablename__ = "devices"
    id = Column(Integer, primary_key=True)
    fingerprint = Column(String, unique=True)
    name = Column(String)
