/*
 * WaveFileTest.cpp
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */

#include "wave/WaveFile.h"
#include "gtest/gtest.h"

class WaveFileTest: public ::testing::Test {
public:
	static const int surrounding = 10;
	static const double brodleyParameter = 0.9;
};

TEST_F(WaveFileTest, throwsEceptionWhenFileDoesNotExist) {

	ASSERT_THROW(WaveFile("nonExistingFile.wav"), std::bad_alloc);

}
