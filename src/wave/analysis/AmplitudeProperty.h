/*
 * AmplitudeProperty.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef AMPLITUDEPROPERTY_H_
#define AMPLITUDEPROPERTY_H_
#include "Property.h"
#include <cmath>

class AmplitudeProperty: public Property {
private:

	double rangeFromPercent;
	double rangeToPercent;

public:

	AmplitudeProperty(double rangeFromPercent = 0,
			double rangeToPercent = 100) {
		this->rangeFromPercent = rangeFromPercent;
		this->rangeToPercent = rangeToPercent;
	}

	virtual double getValue(Samples& samples) {
		uint32_t firstSample = round(
				(samples.getNumberOfSamples() - 1) * rangeFromPercent / 100.0);
		uint32_t lastSample = round(
				(samples.getNumberOfSamples() - 1) * rangeToPercent / 100.0);

		double result = 0.0;
		for (unsigned int i = firstSample; i <= lastSample; ++i) {
			double sample = samples.getSample(i);
			if (fabs(sample) > result) {
				result = fabs(sample);
			}
		}
		return result;
	}

	virtual string getName() {
		std::stringstream resutl;
		resutl << "amplitude_from_" << rangeFromPercent << "_to_"
				<< rangeToPercent << "_percent";
		return resutl.str();
	}

};

#endif /* AMPLITUDEPROPERTY_H_ */
