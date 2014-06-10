/*
 * FastFourierTransformFilter.h
 *
 *  Created on: 8 cze 2014
 *      Author: aldor
 */

#ifndef FASTFOURIERTRANSFORMFILTER_H_
#define FASTFOURIERTRANSFORMFILTER_H_
#include <cstdint>

#include <complex>

#include "kissfft.hh"

#include "wave/Samples.h"
#include "wave/processing/Filter.h"



class FastFourierTransformFilter: public Filter {

public:
	void applyOn(Samples& samples) {

		uint32_t n = samples.numberOfSamples;
		if (n%2 !=0) n--;

		kissfft<double> FFT(n/2.0, false);
		FFT.transform(samples.samples, samples.samples );

	}
	void applyOn(cx * samples, uint32_t n) {


	if (n==0)
		throw "Error 0 samples!";
	cx * output = new cx[n];

	kissfft<double> FFT(n, false);
	FFT.transform(samples, output);
	std::memcpy(samples, output, sizeof(cx) * n);
	delete[] output;

	}

};



#endif /* FASTFOURIERTRANSFORMFILTER_H_ */
