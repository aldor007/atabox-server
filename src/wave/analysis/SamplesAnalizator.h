/*
 * WaveFileAnalizator.h
 *
 *  Created on: Apr 2, 2014
 *      Author: mj
 */

#ifndef WAVEFILEANALIZATOR_H_
#define WAVEFILEANALIZATOR_H_
#include "../Samples.h"
#include "WaveProperties.h"
#include <cmath>

class SamplesAnalizator {
public:
	SamplesAnalizator();
	virtual ~SamplesAnalizator();
	double findAmplitude(Samples& samples);
	int countZeroCrossings(Samples& samples);
	double percentageAbove(Samples& samples, double percentOfMax);
	double percetnageBelow(Samples& samples, double percentOfMax);
	WaveProperties getAllProperties(Samples& samples);
	// FIXME Issue #22 write test for this function and uncomment
	//	double findPeriod(NormalizedSamplesList& samples);

};

#endif /* WAVEFILEANALIZATOR_H_ */
