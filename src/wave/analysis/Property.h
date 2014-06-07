/*
 * Property.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef PROPERTY_H_
#define PROPERTY_H_
#include "../Samples.h"
class Property {
public:
	virtual ~Property(){};
	virtual double getValue(Samples& samples) = 0;
	//TODO getJSON()
};

#endif /* PROPERTY_H_ */
