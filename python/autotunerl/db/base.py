"""SQLAlchemy base and session."""
from sqlalchemy.orm import declarative_base, sessionmaker
from sqlalchemy import create_engine
import os

DATABASE_URL = os.getenv("DATABASE_URL", "sqlite:///./autotunerl.db")
engine = create_engine(DATABASE_URL)
SessionLocal = sessionmaker(bind=engine)
Base = declarative_base()
