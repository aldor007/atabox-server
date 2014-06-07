/*
 * ZeroCrossingsProperty.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef ZeroCrossingsProperty_H_
#define ZeroCrossingsProperty_H_
#include "Property.h"

class ZeroCrossingsProperty: Property {
public:
	virtual double getValue(Samples& samples) {
		int result = 0;
		for (unsigned int i = 0; i < samples.getNumberOfSamples() - 1; ++i) {
			double sample = samples.getSample(i);
			double nextSample = samples.getSample(i + 1);
			if (sample * nextSample <= 0) {
				++result;
			}
		}
		return result;
	}


	virtual string getName() {
		return "zeroCrossings";
	}

};

#endif /* ZeroCrossingsProperty_H_ */
