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


TEST_F(PropertiesComparatorTest, theDiffrenWordReturnsNotZeroDistance) {
	//given
	WaveFile waveFile("test/wave/dziekuje32bit.wav");
	WaveFile waveFile2("test/wave/prosze32bit.wav");
	WaveFileAnalizator analizator;
	WaveProperties properties, properties2;
	properties = analizator.getAllProperties(waveFile);
	properties2 = analizator.getAllProperties(waveFile2);
	//when
	PropertiesComparator comparator;
	double result;
	result = comparator.getDistance(properties, properties2);
	//then

	ASSERT_NE(result, 0);
}
TEST_F(PropertiesComparatorTest, theSameWordDiffrentBitsReturnsZeroDistance) {
	//given
	WaveFile waveFile("test/wave/dziekuje32bit.wav");
	WaveFile waveFile2("test/wave/dziekuje8bit.wav");
	WaveFileAnalizator analizator;
	WaveProperties properties, properties2;
	properties = analizator.getAllProperties(waveFile);
	properties2 = analizator.getAllProperties(waveFile2);
	//when
	PropertiesComparator comparator;
	double result;
	result = comparator.getDistance(properties, properties2);
	//then

	ASSERT_NE(result, 0);
}
//TODO
/*
TEST_F(PropertiesComparatorTest, theSameFileReturnZeroDistanceHidghNoise) {
	//given
	WaveFile waveFile("test/wave/dziekuje32bit.wav");
	WaveFile waveFile2("test/wave/dziekuje32bitHighNoise.wav");
	WaveFileAnalizator analizator;
	WaveProperties properties, properties2;
	properties = analizator.getAllProperties(waveFile);
	properties2 = analizator.getAllProperties(waveFile2);
	//when
	PropertiesComparator comparator;
	double result;
	result = comparator.getDistance(properties, properties2);
	//then

	ASSERT_FLOAT_EQ(result, 0);
}
*/
