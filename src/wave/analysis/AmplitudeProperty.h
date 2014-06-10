/*
 * AmplitudeProperty.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef AMPLITUDEPROPERTY_H_
#define AMPLITUDEPROPERTY_H_
#include "PropertyWithRange.h"

class AmplitudeProperty: public PropertyWithRange {
public:

	AmplitudeProperty(double rangeFromPercent = 0, double rangeToPercent = 100, double weight = 1.0) :
			PropertyWithRange(rangeFromPercent, rangeToPercent, weight) {
	}

	AmplitudeProperty(double weight ) :
			PropertyWithRange(0, 100, weight) {
	}
	virtual double getValue(const Samples& samples) {

		double result = 0.0;
		for (unsigned int i = firstSample(samples); i <= lastSample(samples);
				++i) {
			double sample = samples.getSample(i);
			if (fabs(sample) > result) {
				result = fabs(sample);
			}
		}
		return result;
	}


	virtual string getName() {
		return getNameWithRanges("amplitude");
	}
	virtual double getWeight() {
		return 2.0;
	}
}
;

#endif /* AMPLITUDEPROPERTY_H_ */
