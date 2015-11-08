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
#include <global.h>
#include "aquila/source/SignalSource.h"

#include "WaveFile.h"
#include "WaveUtils.h"



class FastFourierTransformFilter;
class Samples : public Aquila::SignalSource {
public:
	friend class FastFourierTransformFilter;
public:
	Samples(WaveFile & waveFile);
	Samples(WaveFile && waveFile);
	virtual ~Samples();
	virtual atabox::SampleType getSample(unsigned int i) const;
	virtual atabox::ComplexType getSampleCx(unsigned int i) const;
	virtual void setSample(uint32_t index, atabox::SampleType value);
	virtual uint32_t getNumberOfSamples() const;
	virtual double getLenghtInSeconds() const;
	atabox::SampleType& operator[](unsigned int);
	atabox::SampleType operator[](unsigned int) const;
	void setSamplesData(const atabox::SampleType *, unsigned int, atabox::FrequencyType);
	void setSampleFrequency(atabox::FrequencyType);
	Samples();
protected:
	uint32_t numberOfSamples;
	double lenghtInSeconds;
	void decode(WaveFile&);

};

#endif /* SAMPLELIST_H_ */
