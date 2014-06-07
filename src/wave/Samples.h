/*
 * SampleList.h
 *
 *  Created on: 30 kwi 2014
 *      Author: mj
 */

#ifndef SAMPLELIST_H_
#define SAMPLELIST_H_
#include <stdint.h>
#include <complex>

#include "WaveFile.h"
#include "WaveUtils.h"

typedef std::complex<double> cx;



class Samples {
public:
	friend cx * fast_fourier_transform(Samples& a);
public:
	Samples(WaveFile & waveFile);
	Samples(WaveFile && waveFile);
	virtual ~Samples();
	virtual double operator[](unsigned int i);
	virtual double getSample(unsigned int i);
	virtual void setSample(uint32_t index, double value);
	virtual uint32_t getNumberOfSamples();
	virtual double getLenghtInSeconds();
	void setSampleListData(uint32_t numberOfSamples, cx * data);
	Samples();
protected:
	cx * samples = nullptr;
	uint32_t numberOfSamples;
	double lenghtInSeconds;
	uint32_t sampleRate;
};

#endif /* SAMPLELIST_H_ */
