/*
 * Property.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef PROPERTY_H_
#define PROPERTY_H_
#include <string>

#include "wave/Samples.h"
#include "utils/jsonextend.h"

class Property {

public:
	 Property(double weight = 1.0){
		m_weight = weight;
	};
	virtual ~Property(){
	};
	virtual double getValue(const Samples& samples) = 0;
	virtual std::string getName() = 0;
	virtual double getWeight() {
		return m_weight;
	}
	virtual jsonextend getJSON(const Samples& samples) {
		jsonextend value;
		double val = getValue(samples);
		value[getName()] = web::json::value::number(val);
		return value;
	}


protected:
	double m_weight;
};

#endif /* PROPERTY_H_ */
