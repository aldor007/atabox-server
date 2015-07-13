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


#include "wave/Samples.h"
#include "wave/processing/Filter.h"



class FastFourierTransformFilter: public Filter {

public:
	void applyOn(Samples& samples) {

		uint32_t n = samples.numberOfSamples;
		if (n%2 !=0) n--;


	}
	void applyOn(std::complex<double> * samples, uint32_t n) {


	}

};



#endif /* FASTFOURIERTRANSFORMFILTER_H_ */
