/*
 * PowerProperty.h
 *
 *  Created on: 8 cze 2014
 *      Author: mj
 */

#ifndef POWERPROPERTY_H_
#define POWERPROPERTY_H_
#include "Property.h"
#include <cmath>

class AverageValueProperty : public Property {
private:

	double rangeFromPercent;
	double rangeToPercent;

public:

	AverageValueProperty(double rangeFromPercent = 0, double rangeToPercent =
			100) {
		this->rangeFromPercent = rangeFromPercent;
		this->rangeToPercent = rangeToPercent;
	}

	virtual double getValue(Samples& samples) {
		uint32_t firstSample = round((samples.getNumberOfSamples()-1) * rangeFromPercent
				/ 100.0);
		uint32_t lastSample = round((samples.getNumberOfSamples()-1) * rangeToPercent
				/ 100.0);

		double result = 0.0;
		uint32_t numberOfSamplesInRange = 0;
		for (unsigned int i = firstSample; i <= lastSample; ++i) {
			double sample = samples.getSample(i);
			result += fabs(sample);
			numberOfSamplesInRange++;
		}
		return result/numberOfSamplesInRange;
	}

	virtual string getName() {
		std::stringstream resutl;
		resutl << "averageValue_from_" << rangeFromPercent << "_to_"
				<< rangeToPercent << "_percent";
		return resutl.str();
	}

};


#endif /* POWERPROPERTY_H_ */
