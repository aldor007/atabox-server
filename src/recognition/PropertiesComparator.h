/*
 * PropertiesComparator.h
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#ifndef PROPERTIESCOMPARATOR_H_
#define PROPERTIESCOMPARATOR_H_
#include "wave/WaveProperties.h"
#include <math.h>

class PropertiesComparator {
public:
	PropertiesComparator();
	~PropertiesComparator();
	double getDistance(WaveProperties newSample,
			WaveProperties patternSample);
private:
	double relativeError(double newSample, double patternSample);
};

#endif /* PROPERTIESCOMPARATOR_H_ */
