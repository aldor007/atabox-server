/*
 * WaveUtilsTest.cpp
 *
 *  Created on: 2 maj 2014
 *      Author: mj
 */

#include <wave/WaveUtils.h>
#undef U
#include "gtest/gtest.h"

class WaveUtilsTest: public ::testing::Test {

};

TEST_F(WaveUtilsTest, getMaxOfRange) {
	// given
	unsigned int bitsPerSample = 8;
	// when
	int result = WaveUtils::getMaxOfRange(bitsPerSample);
	// then
	ASSERT_EQ(127, result);
}
TEST_F(WaveUtilsTest, getMaxOfRange32bity) {
	// given
	unsigned int bitsPerSample = 32;
	// when
	int result = WaveUtils::getMaxOfRange(bitsPerSample);
	// then
	ASSERT_EQ(2147483647, result);
}
TEST_F(WaveUtilsTest, calculateLenghtInSeconds) {
	// given (data from bells.wave)
	unsigned int sampleRate = 11025;
	uint32_t numberOfSamples = 79334;
	// when
	double result = WaveUtils::calculateLenghtInSeconds(numberOfSamples, sampleRate);
	// then
	ASSERT_NEAR(7.196, result, 0.001);
}
