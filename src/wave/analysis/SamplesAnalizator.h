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
#include "Property.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;



class SamplesAnalizator {
public:
	SamplesAnalizator();
	virtual ~SamplesAnalizator();
	vector<Property*> properties;
	void addProperty(Property & property);
	void getPropertiesSummary(Samples & samples);

	// TODO move below to subclasses of Property
	double findAmplitude(Samples& samples);
	int countZeroCrossings(Samples& samples);
	double percentageAbove(Samples& samples, double percentOfMax);
	double percetnageBelow(Samples& samples, double percentOfMax);
	WaveProperties getAllProperties(Samples& samples);
	// FIXME Issue #22 write test for this function and uncomment
	//	double findPeriod(NormalizedSamplesList& samples);

};

#endif /* WAVEFILEANALIZATOR_H_ */
