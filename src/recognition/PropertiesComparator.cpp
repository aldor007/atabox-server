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

double PropertiesComparator::getSimilarityRatio(WaveProperties newSample,
		WaveProperties patternSample) {
	// TODO PropertiesComparator not yet implemented
	double result = 0.0;
	result += relativeError(newSample.aplitude, patternSample.aplitude);
	result += relativeError(newSample.zeroCrossings, patternSample.zeroCrossings);
	return result;
}

double PropertiesComparator::relativeError(double newSample,
		double patternSample) {
	return fabs(newSample-patternSample)/patternSample;
}
