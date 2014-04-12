/*
 * PropertiesComparator.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "PropertiesComparator.h"

PropertiesComparator::PropertiesComparator() {
	// TODO Auto-generated constructor stub

}

PropertiesComparator::~PropertiesComparator() {
	// TODO Auto-generated destructor stub
}

double PropertiesComparator::getDistance(WaveProperties newSample,
		WaveProperties patternSample) {
	// TODO  not all properties implemented
	// TODO to much copy paste!
	double result = 0.0;
	if (patternSample.amplitude != 0) {
		result += relativeError(newSample.amplitude, patternSample.amplitude);
	}
	if (patternSample.zeroCrossings != 0) {
		result += relativeError(newSample.zeroCrossings,
				patternSample.zeroCrossings);
	}
	return result;
}

double PropertiesComparator::relativeError(double newSample,
		double patternSample) {
	return fabs(newSample - patternSample) / patternSample;
}
