/*
 * AmplitudeProperty.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef AMPLITUDEPROPERTY_H_
#define AMPLITUDEPROPERTY_H_
#include "Property.h"

class AmplitudeProperty: Property {
public:
	virtual double getValue(Samples& samples) {
		double result = 0;
		for (unsigned int i = 0; i < samples.getNumberOfSamples(); ++i) {
			double sample = samples.getSample(i);
			if (fabs(sample) > result) {
				result = fabs(sample);
			}
		}
		return result;
	}


	virtual string getName() {
		return "amplitude";
	}

};

#endif /* AMPLITUDEPROPERTY_H_ */
