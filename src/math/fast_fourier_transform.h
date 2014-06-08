#include <complex>

#include "kissfft.hh"

#include "wave/Samples.h"

template<typename T>
cx * fast_fourier_transform(T *a, uint32_t n) {

	if (n==0)
		throw "Error 0 samples!";
	cx * output = new cx[n];

	kissfft<double> FFT(n, false);
	FFT.transform(a, output);
	return output;

}
//template <>
cx * fast_fourier_transform(Samples& a) {

	uint32_t n = a.numberOfSamples;
	if (n%2 !=0) n--;

	return fast_fourier_transform(a.samples, n);

}
