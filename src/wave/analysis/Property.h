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
protected:
	double m_weight;
public:
	 Property(double weight = 1.0){
		m_weight = weight;
	};
	virtual ~Property(){
	};
	virtual double getValue(const Samples& samples) = 0;
	virtual string getName() = 0;
	virtual double getWeight() {
		return m_weight;
	}

	//TODO getJSON()
};

#endif /* PROPERTY_H_ */
