/*
 * PropertyWithRange.h
 *
 *  Created on: 8 cze 2014
 *      Author: mj
 */

#ifndef PROPERTYWITHRANGE_H_
#define PROPERTYWITHRANGE_H_
#include "Property.h"
#include <cmath>

class PropertyWithRange: public Property {
protected:
	double rangeFromPercent;
	double rangeToPercent;
	double firstSample(const Samples& samples) {
		return round(
				(samples.getNumberOfSamples() - 1) * rangeFromPercent / 100.0);
	}
	double lastSample(const Samples& samples) {
		return round(
				(samples.getNumberOfSamples() - 1) * rangeToPercent / 100.0);
	}
	PropertyWithRange(double rangeFromPercent, double rangeToPercent, double weight = 1.0): Property(weight) {
		this->rangeFromPercent = rangeFromPercent;
		this->rangeToPercent = rangeToPercent;
	}

	std::string getNameWithRanges(std::string className) {
		std::stringstream resutl;
		resutl << className << "_from_" << rangeFromPercent << "_to_"
				<< rangeToPercent << "_percent";
		return resutl.str();
	}

public:
	virtual ~PropertyWithRange() {};
};

#endif /* PROPERTYWITHRANGE_H_ */
