/*
 * ZeroCrossingsProperty.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef ZeroCrossingsProperty_H_
#define ZeroCrossingsProperty_H_
#include "Property.h"
#include <cmath>

class ZeroCrossingsProperty: public Property {
private:

	double rangeFromPercent;
	double rangeToPercent;

public:

	ZeroCrossingsProperty(double rangeFromPercent = 0, double rangeToPercent =
			100) {
		this->rangeFromPercent = rangeFromPercent;
		this->rangeToPercent = rangeToPercent;
	}

	virtual double getValue(Samples& samples) {
		int result = 0;
		uint32_t firstSample =  round((samples.getNumberOfSamples()-1) * rangeFromPercent
				/ 100.0);
		uint32_t lastSample =  round((samples.getNumberOfSamples()-1) * rangeToPercent
				/ 100.0);
		for (unsigned int i = firstSample; i < lastSample; ++i) {
			double sample = samples.getSample(i);
			double nextSample = samples.getSample(i + 1);
			if (sample * nextSample <= 0) {
				++result;
			}
		}
		return result;
	}

	virtual string getName() {
		std::stringstream resutl;
		resutl << "zeroCrossings_from_" << rangeFromPercent << "_to_"
				<< rangeToPercent << "_percent";
		return resutl.str();
	}

};

#endif /* ZeroCrossingsProperty_H_ */
