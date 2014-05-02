/*
 * NormalizedSampleListMock.h
 *
 *  Created on: 30 kwi 2014
 *      Author: mj
 */

#ifndef NORMALIZEDSAMPLELISTMOCK_H_
#define NORMALIZEDSAMPLELISTMOCK_H_
#include "wave/NormalizedSamplesList.h"
#undef U

#include "gmock/gmock.h"

class NormalizedSampleListMock: public NormalizedSamplesList {
public:
	NormalizedSampleListMock();
	virtual ~NormalizedSampleListMock();
	MOCK_METHOD0(getNumberOfSamples, uint32_t());
	MOCK_METHOD1(getSample, double(unsigned int i));
};

#endif /* NORMALIZEDSAMPLELISTMOCK_H_ */
