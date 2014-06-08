/*
 * PropertiesComparator.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "PropertiesComparator.h"

PropertiesComparator::PropertiesComparator() {

}

PropertiesComparator::~PropertiesComparator() {
}

double PropertiesComparator::getDistance(jsonextend newSample,
		jsonextend patternSample) {
	// TODO  not all properties implemented
	// TODO to much copy paste!
	double result = 0.0;
	for (auto iter = newSample.as_object().cbegin(); iter != newSample.as_object().cend(); iter++) {
		result += relativeError(iter->second.as_double(), patternSample[iter->first].as_double());


	}

	return result;
}

double PropertiesComparator::relativeError(double newSample,
		double patternSample) {
	return fabs(newSample - patternSample) / patternSample;
}
