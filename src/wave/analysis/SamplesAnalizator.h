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


class SamplesAnalizator {
public:
	SamplesAnalizator();
	virtual ~SamplesAnalizator();
	std::vector<Property*> properties;
	//virtual
	void addProperty(Property & property);
	//virtual
	void addProperty(Property * property);
	virtual jsonextend getPropertiesSummary(Samples & samples);
};

#endif /* WAVEFILEANALIZATOR_H_ */
