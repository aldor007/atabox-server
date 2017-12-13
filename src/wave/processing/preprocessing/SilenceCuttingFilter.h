/*
 * SilenceCuttingFilter.h
 *
 *  Created on: 6 cze 2014
 *      Author: mj
 */

#ifndef SILENCECUTTINGFILTER_H_
#define SILENCECUTTINGFILTER_H_
#include "wave/processing/Filter.h"

class SilenceCuttingFilter: public Filter {
	double treshold;

public:
	SilenceCuttingFilter(double threshold) {
		this->treshold = threshold;
	}
	void applyOn(Samples &samples) {
		uint32_t lastBadFromBeginning = -1;
		uint32_t lastGoodFromMiddle = samples.getNumberOfSamples();

		bool beginningFound = false;

		for (uint32_t i = 0; i < samples.getNumberOfSamples(); ++i) {
			double sample = samples.getSample(i);
			if (fabs(sample) < treshold) {
				if (!beginningFound) {
					lastBadFromBeginning = i;
				}
			} else {
				beginningFound = true;
				lastGoodFromMiddle = i;
			}
		}

		size_t numberOfSamples = samples.getNumberOfSamples();
		int numberOfFramesToDelete = (lastBadFromBeginning+1) + (samples.getNumberOfSamples()-1-lastGoodFromMiddle);
		uint32_t sizeOfNewArray = numberOfSamples
				- numberOfFramesToDelete;
		double * framesWithoutSilence = new double[sizeOfNewArray];
		for (uint32_t i = 0; i < sizeOfNewArray; ++i) {
			uint32_t w = lastBadFromBeginning + 1 + i;
			if (w < numberOfSamples) {
				framesWithoutSilence[i] = samples.getSample(lastBadFromBeginning+1+i);
			} else {
				framesWithoutSilence[i] = 0;
			}
		}

		samples.setSamplesData(framesWithoutSilence, sizeOfNewArray, samples.getSampleFrequency());
		delete[] framesWithoutSilence;

	}
	~SilenceCuttingFilter(){};
};

#endif /* SILENCECUTTINGFILTER_H_ */
