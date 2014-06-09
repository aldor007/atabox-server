/*
 * Property.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef PROPERTY_H_
#define PROPERTY_H_
#include <string>
#include "../Samples.h"

using std::string;

class Property {
public:
	virtual ~Property(){};
	virtual double getValue(const Samples& samples) = 0;
	virtual string getName() = 0;

	//TODO getJSON()
};

#endif /* PROPERTY_H_ */
