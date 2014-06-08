/*
 * hann_window.h
 *
 *  Created on: 8 cze 2014
 *      Author: aldor
 */

#ifndef HANN_WINDOW_H_
#define HANN_WINDOW_H_
#include "wave/processing/Filter.h"
#include <cmath>


class HannWindowFilter: public Filter {

public:
	void applyOn(Samples& samples) {
		uint32_t size = samples.getNumberOfSamples();
		for (uint32_t i = 0; i < size; i++) {
		    double multiplier = 0.5 * (1 - cos(2*M_PI*i/size));
		   samples[i] *=  multiplier;
		}

	}

};




#endif /* HANN_WINDOW_H_ */
