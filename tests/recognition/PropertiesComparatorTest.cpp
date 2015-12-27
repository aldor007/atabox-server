/*
 * PropertiesComparatorTest.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "recognition/PropertiesComparator.h"

#include "wave/WaveFile.h"
// #include "SamplesAnalyzer.h"
#include "wave/Samples.h"
#undef U //XXX: potrzebne zeby sie kompilowala z casablanca
//#include "gtest/gtest.h" XXX: WTF!!!! nie kompiluje sie u mnie jak to jest. (Po reinstalacji systemuu)

#ifndef GTEST_H_
	#define GTEST_H_
	#include "gtest/gtest.h"
#endif

class PropertiesComparatorTest: public ::testing::Test {

};
/*
TEST_F(PropertiesComparatorTest, theSameFileReturnsZeroDistance) {
	//given
	WaveFile waveFile("test/wave/waveFiles/dziekuje32bit.wav");
	Samples samples(waveFile);
	SamplesAnalyzer analizator;
	WaveProperties properties;
	properties = analizator.getAllProperties(samples);
	//when
	PropertiesComparator comparator;
	double result;
	result = comparator.getDistance(properties, properties);
	//then
	ASSERT_FLOAT_EQ(result, 0);
}


TEST_F(PropertiesComparatorTest, theDiffrenWordReturnsNotZeroDistance) {
	//given
	WaveFile waveFile1("test/wave/waveFiles/dziekuje32bit.wav");
	Samples samples1(waveFile1);
	WaveFile waveFile2("test/wave/waveFiles/prosze32bit.wav");
	Samples samples2(waveFile2);
	SamplesAnalyzer analizator;
	WaveProperties properties, properties2;
	properties = analizator.getAllProperties(samples1);
	properties2 = analizator.getAllProperties(samples2);
	//when
	PropertiesComparator comparator;
	double result;
	result = comparator.getDistance(properties, properties2);
	//then

	ASSERT_NE(result, 0);
}
TEST_F(PropertiesComparatorTest, theSameWordDiffrentBitsReturnsZeroDistance) {
	//given
	WaveFile waveFile1("test/wave/waveFiles/dziekuje32bit.wav");
	Samples samples1(waveFile1);
	WaveFile waveFile2("test/wave/waveFiles/dziekuje8bit.wav");
	Samples samples2(waveFile2);

	SamplesAnalyzer analizator;
	WaveProperties properties, properties2;
	properties = analizator.getAllProperties(samples1);
	properties2 = analizator.getAllProperties(samples2);
	//when
	PropertiesComparator comparator;
	double result;
	result = comparator.getDistance(properties, properties2);

	//then
	ASSERT_NE(result, 0);
}

*/
//TODO
/*
TEST_F(PropertiesComparatorTest, theSameFileReturnZeroDistanceHidghNoise) {
	//given
	WaveFile waveFile("test/wave/waveFiles/dziekuje32bit.wav");
	WaveFile waveFile2("test/wave/waveFiles/dziekuje32bitHighNoise.wav");
	SamplesAnalyzer analizator;
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
