/*
 * NormalizedSampleListMock.h
 *
 *  Created on: 30 kwi 2014
 *      Author: mj
 */

#ifndef NORMALIZEDSAMPLELISTMOCK_H_
#define NORMALIZEDSAMPLELISTMOCK_H_
#include "wave/Samples.h"
#undef U

#include "gmock/gmock.h"

class SamplesMock: public Samples {
public:
	SamplesMock(){};
	virtual ~SamplesMock(){};
	MOCK_CONST_METHOD0(getNumberOfSamples, uint32_t());
	MOCK_CONST_METHOD0(getLenghtInSeconds, double());
	MOCK_CONST_METHOD1(getSample, double(unsigned int i));
	virtual double operator[](unsigned int i) const {
		return getSample(i);
	}
};

#endif /* NORMALIZEDSAMPLELISTMOCK_H_ */
