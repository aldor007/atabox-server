/*
 * PowerProperty.h
 *
 *  Created on: 8 cze 2014
 *      Author: mj
 */

#ifndef POWERPROPERTY_H_
#define POWERPROPERTY_H_
#include "PropertyWithRange.h"


class AverageValueProperty : public PropertyWithRange {
public:
	AverageValueProperty(double rangeFromPercent = 0, double rangeToPercent =
			100): PropertyWithRange(rangeFromPercent, rangeToPercent) {
	}

	virtual double getValue(Samples& samples) {

		double result = 0.0;
		uint32_t numberOfSamplesInRange = 0;
		for (unsigned int i = firstSample(samples); i <= lastSample(samples); ++i) {
			double sample = samples.getSample(i);
			result += fabs(sample);
			numberOfSamplesInRange++;
		}
		return result/numberOfSamplesInRange;
	}

	virtual string getName() {
		return getNameWithRanges("averageValue");
	}

};


#endif /* POWERPROPERTY_H_ */
