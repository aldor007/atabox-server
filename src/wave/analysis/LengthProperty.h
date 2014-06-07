/*
 * LengthProperty.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef LENGTHPROPERTY_H_
#define LENGTHPROPERTY_H_
#include "Property.h"
class LengthProperty : Property {
public:
	LengthProperty();
	double getValue(Samples& samples);
};

#endif /* LENGTHPROPERTY_H_ */
