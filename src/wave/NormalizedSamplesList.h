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
#include "WaveUtils.h"

class NormalizedSamplesList {
public:
	NormalizedSamplesList(WaveFile & waveFile);
	virtual ~NormalizedSamplesList();
	virtual double operator[](unsigned int i);
	virtual double getSample(unsigned int i);
	virtual uint32_t getNumberOfSamples();
	virtual double getLenghtInSeconds();
	void setSampleListData(uint32_t numberOfSamples, double * data);
protected:
	NormalizedSamplesList();
	double *samples = nullptr;
	uint32_t numberOfSamples;
	double lenghtInSeconds;
	uint32_t sampleRate;
};

#endif /* SAMPLELIST_H_ */
