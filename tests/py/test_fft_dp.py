from autotunerl.dp.fft_factorization import factorize


def test_fft_factorization_placeholder():
    assert factorize(16) == [16]
