"""Logging utilities."""
import logging
import json


def get_logger(name: str) -> logging.Logger:
    logger = logging.getLogger(name)
    if not logger.handlers:
        handler = logging.StreamHandler()
        formatter = logging.Formatter('%(message)s')
        handler.setFormatter(formatter)
        logger.addHandler(handler)
        logger.setLevel(logging.INFO)
    return logger


def log_json(logger: logging.Logger, **kwargs) -> None:
    logger.info(json.dumps(kwargs))
