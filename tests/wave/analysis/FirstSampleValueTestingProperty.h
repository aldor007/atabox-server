/*
 * FirstSampleValueTestingProperty.h
 *
 *  Created on: 8 cze 2014
 *      Author: mj
 */

#ifndef FIRSTSAMPLEVALUETESTINGPROPERTY_H_
#define FIRSTSAMPLEVALUETESTINGPROPERTY_H_
#include "wave/analysis/Property.h"

class FirstSampleValueTestingProperty: public Property {
public:
	virtual double getValue(const Samples& samples) {
		return samples.getSample(0);
	}


	virtual string getName() {
		return "firstSampleValue";
	}

};

#endif /* FIRSTSAMPLEVALUETESTINGPROPERTY_H_ */
