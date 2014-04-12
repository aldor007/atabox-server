/*
 * PropertiesComparatorTest.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "recognition/PropertiesComparator.h"

#include "gtest/gtest.h"
#include "wave/WaveFile.h"
#include "wave/WaveFileAnalizator.h"
#include "wave/WaveProperties.h"

class PropertiesComparatorTest: public ::testing::Test {

};

TEST_F(PropertiesComparatorTest, theSameFileReturnsZeroDistance) {
	//given
	WaveFile waveFile("test/wave/dziekuje32bit.wav");
	WaveFileAnalizator analizator;
	WaveProperties properties;
	properties = analizator.getAllProperties(waveFile);
	//when
	PropertiesComparator comparator;
	double result;
	result = comparator.getDistance(properties, properties);
	//then
	ASSERT_FLOAT_EQ(result, 0);
}
