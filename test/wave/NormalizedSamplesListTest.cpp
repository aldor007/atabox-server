/*
 * SampleListTest.cpp
 *
 *  Created on: 30 kwi 2014
 *      Author: mj
 */

#include <wave/NormalizedSamplesList.h>
#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;

class NormalizedSamplesListTest: public ::testing::Test {

};

TEST_F(NormalizedSamplesListTest, canHandleWaveFileReadedFromMemory) {
	//given
	const uint16_t size = 200;
	uint8_t tmpData[size];
	uint16_t bitspersample = 8;
	uint32_t  sampleRate = 60;
	std::memcpy(tmpData + 24, &sampleRate, 4);
	uint8_t currentIndex  = 34;
	std::memcpy(tmpData + currentIndex, &bitspersample, 2);
	currentIndex += 2;
	uint8_t subchunk2Id[] = { 'd', 'a', 't', 'a'};
	std::memcpy(tmpData + currentIndex, &subchunk2Id, 4);
	currentIndex += 4;
	uint16_t numOfChannels = 1;
	std::memcpy(tmpData + 22, &numOfChannels, 2);
	uint32_t subchunk2size = size - currentIndex;
	std::memcpy(tmpData + currentIndex, &subchunk2size, 4);
	currentIndex += 4;
	for (uint8_t i = currentIndex; i < size; i++) {
		tmpData[i] = i;
	}
	WaveFile waveFile(tmpData);
	ASSERT_EQ(waveFile.getBitsPerSample(), bitspersample);
	double result = (currentIndex + 1) / (1<<(bitspersample - 1));
	NormalizedSamplesList test(waveFile);
	ASSERT_EQ(test.getLenghtInSeconds(), 8./3.);
	ASSERT_EQ(test.getNumberOfSamples(), subchunk2size);
	ASSERT_TRUE(test.getSample(0) <= 1);
	ASSERT_EQ(test.getSample(1), result);
}
