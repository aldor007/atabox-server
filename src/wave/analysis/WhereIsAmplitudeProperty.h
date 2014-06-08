/*
 * WhereIsAmplitudeProperty.h
 *
 *  Created on: 8 cze 2014
 *      Author: mj
 */

#ifndef WhereIsAmplitudeProperty_H_
#define WhereIsAmplitudeProperty_H_
#include "Property.h"
#include <cmath>


class WhereIsAmplitudeProperty: public Property {

public:

	virtual double getValue(Samples& samples) {

		double indexOfAmplitude = 0;
		double amplitude = 0.0;
		for (unsigned int i = 0; i < samples.getNumberOfSamples(); ++i) {
			double sample = samples.getSample(i);
			if (fabs(sample) > amplitude) {
				amplitude = fabs(sample);
				indexOfAmplitude = i;
			}
		}
		return (indexOfAmplitude/(samples.getNumberOfSamples()-1))*100;
	}


	virtual string getName() {
		return "whereIsAmplitude";
	}

};

#endif
