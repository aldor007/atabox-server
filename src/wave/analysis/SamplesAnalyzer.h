/*
 * WaveFileAnalizator.h
 *
 *  Created on: Apr 2, 2014
 *      Author: mj
 */

#ifndef WAVEFILEANALIZATOR_H_
#define WAVEFILEANALIZATOR_H_
#include "../Samples.h"
#include "ArrayProperty.h"
#include "MfccProperty.h"
#include <cmath>
#include "Property.h"

#include <iostream>
#include <vector>
#include <string>

#include "utils/jsonextend.h"


class SamplesAnalyzer {
	std::vector<ArrayProperty*> arrayProperties_;
public:
	SamplesAnalyzer();
	virtual ~SamplesAnalyzer();
	std::vector<Property*> properties;
	//virtual
	void addProperty(Property & property);
	//virtual
	void addProperty(Property * property);
	void addArrayProperty(ArrayProperty * property);
	virtual jsonextend getPropertiesSummary(Samples & samples);
	virtual shark::RealVector getProperties(Samples & samples);
	virtual std::vector<double> getPropertiesVector(Samples & samples);
};

#endif /* WAVEFILEANALIZATOR_H_ */
