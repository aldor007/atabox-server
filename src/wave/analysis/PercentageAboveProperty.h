/*
 * PercentageAboveProperty.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef PercentageAboveProperty_H_
#define PercentageAboveProperty_H_
#include "Property.h"

class PercentageAboveProperty: public Property {
	double treshold;

public:
	PercentageAboveProperty(double treshold){
		this->treshold = treshold;
	}
	virtual double getValue(Samples& samples) {
		int aboveCounter = 0;
		int allCounter = 0;

		for (unsigned int i = 0; i < samples.getNumberOfSamples(); ++i) {
			++allCounter;
			double sample = samples.getSample(i);
			if (fabs(sample) > treshold) {
				++aboveCounter;
			}
		}

		return aboveCounter * 1.0 / allCounter;
	}

	virtual string getName() {
		std::stringstream resutl;
		resutl << "percentageAbove_" << this->treshold;
		return resutl.str();
	}

};

#endif /* PercentageAboveProperty_H_ */
