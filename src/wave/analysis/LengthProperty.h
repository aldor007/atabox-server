/*
 * LengthProperty.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef LENGTHPROPERTY_H_
#define LENGTHPROPERTY_H_
#include "Property.h"
class LengthProperty: public Property {
public:
	LengthProperty(double weight = 1.): Property(weight) {

	}
	virtual double getValue(const Samples& samples) {
		return samples.getLenghtInSeconds();
	}


	virtual string getName() {
		return "length";
	}

};

#endif /* LENGTHPROPERTY_H_ */
