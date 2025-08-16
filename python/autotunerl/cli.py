import csv
import json
import subprocess
from pathlib import Path

import typer

app = typer.Typer()

RUNNER = Path(__file__).resolve().parents[2] / "build" / "autotunerl_runner"

@app.command()
def tune(
    op: str = "gemm",
    m: int = 128,
    n: int = 128,
    k: int = 128,
    reps: int = 2,
    out_csv: Path = Path("results.csv"),
):
    params = {
        "tile_m": 8,
        "tile_n": 8,
        "tile_k": 4,
        "wg_x": 8,
        "wg_y": 1,
        "vec_w": 1,
        "unroll_k": 1,
        "lds_tile": 0,
    }
    cmd = [
        str(RUNNER),
        "--op",
        op,
        "--shape",
        f"m={m},n={n},k={k}",
        "--params-json",
        json.dumps(params),
        "--reps",
        str(reps),
    ]
    output = subprocess.check_output(cmd)
    data = json.loads(output)
    write_header = not out_csv.exists()
    with out_csv.open("a", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=data.keys())
        if write_header:
            writer.writeheader()
        writer.writerow(data)
    typer.echo(f"Wrote result to {out_csv}")

@app.command()
def best(csv_path: Path = Path("results.csv")):
    if not csv_path.exists():
        raise typer.Exit(code=1)
    with csv_path.open() as f:
        reader = csv.DictReader(f)
        rows = list(reader)
    if not rows:
        raise typer.Exit(code=1)
    best_row = max(rows, key=lambda r: float(r.get("gflops", 0)))
    typer.echo(json.dumps(best_row))

if __name__ == "__main__":
    app()
