"""Configuration loader."""
from pydantic import BaseSettings


class Settings(BaseSettings):
    database_url: str = "sqlite:///./autotunerl.db"


settings = Settings()
