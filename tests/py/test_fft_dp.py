from autotunerl.dp.fft_factorization import factorize


def test_factorize():
    assert factorize(8) == [2, 2, 2]
