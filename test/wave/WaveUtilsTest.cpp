/*
 * WaveUtilsTest.cpp
 *
 *  Created on: 2 maj 2014
 *      Author: mj
 */

#include <wave/WaveUtils.h>

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
