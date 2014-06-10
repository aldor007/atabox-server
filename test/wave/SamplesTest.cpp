/*
 * SampleListTest.cpp
 *
 *  Created on: 30 kwi 2014
 *      Author: mj
 */

#include <wave/Samples.h>
#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;

class SamplesTest: public ::testing::Test {

};

TEST_F(SamplesTest, canHandleWaveFile8bitsReadedFromMemory) {
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
	for (uint8_t i = 44; i < size; i++) {
		tmpData[i] = i;
	}
	WaveFile waveFile(tmpData, 200);
	ASSERT_EQ(waveFile.getBitsPerSample(), bitspersample);
	int32_t maxOfRange = WaveUtils::getMaxOfRange(bitspersample);
	double result = (double)(((int32_t)currentIndex - 128)/maxOfRange);

	Samples test(waveFile);
	ASSERT_EQ(test.getLenghtInSeconds(), 8./3.);
	ASSERT_EQ(test.getNumberOfSamples(), subchunk2size);
	for (uint8_t i = 0; i< test.getNumberOfSamples(); i++) {
		ASSERT_LE(test.getSample(i), 1.0);
		ASSERT_GE(test.getSample(i), -1.0);
	}
	ASSERT_EQ(test.getSample(0), result);
}
TEST_F(SamplesTest, canHandleWaveFile32bitsReadedFromMemory) {
	//given
	const uint16_t size = 204;
	uint8_t tmpData[size];
	uint16_t bitspersample = 32;
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
	uint32_t subchunk2size = (size - currentIndex)/4;
	std::memcpy(tmpData + currentIndex, &subchunk2size, 4);
	currentIndex += 4;

	for (uint32_t i = currentIndex; i < size; i = i + 4) {
		int32_t tmpValue = i * (-1) * i%2;
		std::memcpy(tmpData + i, &tmpValue, 4);
	}
	WaveFile waveFile(tmpData, 204);
	ASSERT_EQ(waveFile.getBitsPerSample(), bitspersample);
	for (uint8_t i = 0; i< waveFile.getNumberOfSamples(); i++) {
				ASSERT_LE(waveFile[i], 800);
				ASSERT_GE(waveFile.getRawSample(i), -800.0);
			}

	uint32_t maxOfRange = WaveUtils::getMaxOfRange(bitspersample);
	double lengthInSecond = WaveUtils::calculateLenghtInSeconds(subchunk2size/4, sampleRate);
	int32_t tmpResult = 0;
	std::memcpy(&tmpResult, &tmpData[currentIndex], 4);
	double result = (double)(tmpResult/maxOfRange);

	Samples test(waveFile);
	ASSERT_EQ(test.getLenghtInSeconds(), lengthInSecond);
	ASSERT_EQ(test.getNumberOfSamples(), subchunk2size/4);
	ASSERT_EQ(waveFile.getSampleRate(), sampleRate);

	for (uint8_t i = 0; i< test.getNumberOfSamples(); i++) {
		ASSERT_LE(test.getSample(i), 1.0);
		ASSERT_GE(test.getSample(i), -1.0);
	}
	ASSERT_EQ(test.getSample(0), result);
    ASSERT_LE(test.getSample(subchunk2size/4 - 1), 1.0);
    ASSERT_GE(test.getSample(subchunk2size/4 - 1), -1.0);

}
