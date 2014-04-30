/*
 * SampleList.h
 *
 *  Created on: 30 kwi 2014
 *      Author: mj
 */

#ifndef SAMPLELIST_H_
#define SAMPLELIST_H_
#include <stdint.h>
#include "WaveFile.h"

class NormalizedSamplesList {
public:
	NormalizedSamplesList(WaveFile & waveFile);
	virtual ~NormalizedSamplesList();
	virtual double operator[](unsigned int i);
	virtual double getSample(unsigned int i);
	static uint32_t getMaxOfRange(unsigned int bitsPerSample);
	virtual uint32_t getNumberOfSamples();
protected:
	NormalizedSamplesList();
	double *samples = nullptr;
	uint32_t numberOfSamples;
};

#endif /* SAMPLELIST_H_ */
