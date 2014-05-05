#include <iterator>
#include <complex>
#include <cmath>
#include <iostream>
#include <cstdint>
#include <array>

unsigned int bitReverse(unsigned int x, int log2n)
{
	int n = 0;
	for (int i=0; i < log2n; i++) {
		n <<= 1;
		n |= (x & 1);
		x >>= 1;
	}
	return n;
}

template<class T>
std::complex<double>* FastFourierTransform(T &a, uint32_t n)
{
	std::complex<double>* b;
	uint32_t log2n = ceil(log2((double)n));
	uint32_t n2 = 1<<log2n;
	b = new   std::complex<double>[n2];
	const std::complex<double> J(0, 1);
	for (uint32_t i=0; i < n; ++i) {
		b[bitReverse(i, log2n)] = a[i];
	}

	for (uint32_t s = 1; s <= log2n; ++s) {
		uint32_t m = 1 << s;
		uint32_t m2 = m >> 1;
		std::complex<double> w(1, 0);
		std::complex<double> wm = exp(-J * (M_PI / m2));
		for (uint32_t j=0; j < m2; ++j) {
			for (uint32_t k=j; k < n; k+= m) {
				std::complex<double> t = w * b[k + m2];
				std::complex<double> u = b[k];
				b[k] = u + t;
				b[k + m2] = u - t;
			}
		w *= wm;
		}
	}
	return b;
}

