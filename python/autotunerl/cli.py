import typer

app = typer.Typer(help="AutoTunerRL command line interface")


@app.command()
def tune(op: str = typer.Option(..., help="Operation to tune")) -> None:
    """Stub tune command."""
    typer.echo(f"Tuning {op} (stub)")


@app.command()
def best(op: str = typer.Option(..., help="Operation")) -> None:
    """Stub best command."""
    typer.echo(f"Best config for {op} (stub)")


@app.command()
def bench(suite: str = typer.Option(..., help="Benchmark suite")) -> None:
    """Stub bench command."""
    typer.echo(f"Running benchmark suite {suite} (stub)")


if __name__ == "__main__":
    app()
