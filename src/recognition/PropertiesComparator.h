/*
 * PropertiesComparator.h
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#ifndef PROPERTIESCOMPARATOR_H_
#define PROPERTIESCOMPARATOR_H_

#include "utils/jsonextend.h"


#include <cmath>

class PropertiesComparator {
public:
	PropertiesComparator();
	~PropertiesComparator();
	double getDistance(jsonextend newSample,
			jsonextend patternSample);
private:
	double relativeError(double newSample, double patternSample);
};

#endif /* PROPERTIESCOMPARATOR_H_ */
