/*
 * WaveFileMock.h
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */

#ifndef WAVEFILEMOCK_H_
#define WAVEFILEMOCK_H_

#include <wave/WaveFile.h>
#include "gmock/gmock.h"

class WaveFileMock: public WaveFile {
public:
	WaveFileMock();
	~WaveFileMock();
	MOCK_METHOD0(getNumberOfSamples, unsigned int());
	MOCK_METHOD1(getSample, double(unsigned int i));
	MOCK_METHOD0(getBitsPerSample, unsigned int());
	MOCK_METHOD0(getMaxOfRange, uint32_t());

};

#endif /* WAVEFILEMOCK_H_ */
