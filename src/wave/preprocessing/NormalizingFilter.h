/*
 * NormalizingFilter.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef NORMALIZINGFILTER_H_
#define NORMALIZINGFILTER_H_
#include "Filter.h"

class NormalizingFilter: Filter {
private:
	double toLevel;
public:
	NormalizingFilter(double toLevel = 1.0) {
		this->toLevel = toLevel;
	}

	void applyOn(Samples& samples) {
		double max = 0.0;
		for (unsigned int i = 0; i < samples.getNumberOfSamples(); ++i) {
			double sample = samples.getSample(i);
			if (fabs(sample) > max) {
				max = fabs(sample);
			}
		}

		double factor = toLevel / max;
		for (unsigned int i = 0; i < samples.getNumberOfSamples(); ++i) {
			double oldValue = samples.getSample(i);
			samples.setSample(i, oldValue * factor);
		}

	}
};

#endif /* NORMALIZINGFILTER_H_ */
