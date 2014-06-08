/*
 * WaveFileAnalizator.h
 *
 *  Created on: Apr 2, 2014
 *      Author: mj
 */

#ifndef WAVEFILEANALIZATOR_H_
#define WAVEFILEANALIZATOR_H_
#include "../Samples.h"
#include <cmath>
#include "Property.h"

#include <iostream>
#include <vector>
#include <string>

#include "utils/jsonextend.h"


using namespace std;



class SamplesAnalizator {
public:
	SamplesAnalizator();
	virtual ~SamplesAnalizator();
	vector<Property*> properties;
	void addProperty(Property & property);
	void addProperty(Property * property);
	jsonextend getPropertiesSummary(Samples & samples);
};

#endif /* WAVEFILEANALIZATOR_H_ */
