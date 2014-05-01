/*
 * WaveFileAnalizator.h
 *
 *  Created on: Apr 2, 2014
 *      Author: mj
 */

#ifndef WAVEFILEANALIZATOR_H_
#define WAVEFILEANALIZATOR_H_
#include "NormalizedSamplesList.h"
#include "WaveProperties.h"
#include <cmath>

class WaveFileAnalizator {
public:
	WaveFileAnalizator();
	virtual ~WaveFileAnalizator();
	double findAmplitude(NormalizedSamplesList& samples);
	int countZeroCrossings(NormalizedSamplesList& samples);
	double percentageAbove(NormalizedSamplesList& samples, double percentOfMax);
	double percetnageBelow(NormalizedSamplesList& samples, double percentOfMax);
	WaveProperties getAllProperties(NormalizedSamplesList& samples);
	// FIXME Issue #22 write test for this function and uncomment
	//	double findPeriod(NormalizedSamplesList& samples);

};

#endif /* WAVEFILEANALIZATOR_H_ */
