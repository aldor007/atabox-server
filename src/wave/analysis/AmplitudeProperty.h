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

	AmplitudeProperty(double rangeFromPercent = 0, double rangeToPercent = 100) :
			PropertyWithRange(rangeFromPercent, rangeToPercent) {
	}

	virtual double getValue(Samples& samples) {

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

}
;

#endif /* AMPLITUDEPROPERTY_H_ */
