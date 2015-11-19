/*
 * ZeroCrossingsProperty.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef ZeroCrossingsProperty_H_
#define ZeroCrossingsProperty_H_
#include "PropertyWithRange.h"

class ZeroCrossingsProperty: public PropertyWithRange {
public:
	ZeroCrossingsProperty(double rangeFromPercent = 0, double rangeToPercent =
			100, double weight = 1.0) : PropertyWithRange(rangeFromPercent, rangeToPercent, weight){
	}

	virtual double getValue(const Samples& samples) {
		int result = 0;

		for (unsigned int i = firstSample(samples); i < lastSample(samples); ++i) {
			double sample = samples.getSample(i);
			double nextSample = samples.getSample(i + 1);
			if (sample * nextSample <= 0) {
				++result;
			}
		}
		return result;
	}


	virtual std::string getName() {
		return getNameWithRanges("zeroCrossings");
	}

};

#endif /* ZeroCrossingsProperty_H_ */
