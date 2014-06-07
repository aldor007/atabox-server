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
};

#endif /* WAVEFILEANALIZATOR_H_ */
