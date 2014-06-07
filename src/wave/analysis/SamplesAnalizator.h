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

#include "cpprest/json.h"
namespace webjs = web::json;

using namespace std;



class SamplesAnalizator {
public:
	SamplesAnalizator();
	virtual ~SamplesAnalizator();
	vector<Property*> properties;
	void addProperty(Property & property);
	webjs::value getPropertiesSummary(Samples & samples);
};

#endif /* WAVEFILEANALIZATOR_H_ */
