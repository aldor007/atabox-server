/*
 * ZeroCrossingsPropertyPropertyTest.cpp
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SamplesMock.h"
#include "wave/analysis/ZeroCrossingsProperty.h"

using ::testing::Return;

class ZeroCrossingsPropertyPropertyTest: public ::testing::Test {

};

TEST_F(ZeroCrossingsPropertyPropertyTest, returnCorrectValueOfPropertyForAllSamples) {
	//given
	SamplesMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(-0.12));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(-0.130));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.148));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(0.130));
	ON_CALL(samples, getSample(4)).WillByDefault(Return(-0.1));
	ZeroCrossingsProperty property;

	//when
	int zeroCrossings = property.getValue(samples);

	//then
	ASSERT_EQ(zeroCrossings, 2);
}

TEST_F(ZeroCrossingsPropertyPropertyTest, returnsCorrectNameForAllSamples) {
	//given
	ZeroCrossingsProperty property;

	//when
	string name = property.getName();

	//then
	ASSERT_STRCASEEQ("zeroCrossings_from_0_to_100_percent", name.c_str());
}

TEST_F(ZeroCrossingsPropertyPropertyTest, realFileHasPositiveNumberOfZeroCrossings) {
	//given
	WaveFile waveFile("test/wave/waveFiles/dziekuje32bit.wav");
	Samples samples(waveFile);
	ZeroCrossingsProperty property;

	//when
	int zeroCrossings = property.getValue(samples);

	//then
	ASSERT_GT(zeroCrossings, 0);
}


TEST_F(ZeroCrossingsPropertyPropertyTest, returnCorrectValueOfPropertyForPartOfSamples) {
	//given
	SamplesMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(10));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(-0.12));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(0.130));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(-0.148));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(0.130));
	ON_CALL(samples, getSample(4)).WillByDefault(Return(-0.1));
	ON_CALL(samples, getSample(5)).WillByDefault(Return(0.1));
	ON_CALL(samples, getSample(6)).WillByDefault(Return(-0.1));
	ON_CALL(samples, getSample(7)).WillByDefault(Return(0.1));
	ON_CALL(samples, getSample(8)).WillByDefault(Return(-0.1));
	ON_CALL(samples, getSample(9)).WillByDefault(Return(0.1));
	ZeroCrossingsProperty property(20, 30);

	//when
	int zeroCrossings = property.getValue(samples);

	//then
	ASSERT_EQ(zeroCrossings, 1);
}
TEST_F(ZeroCrossingsPropertyPropertyTest, returnCorrectValueOfPropertyForHalfOfSamples) {
	//given
	SamplesMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(10));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(-0.12));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(0.130));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(-0.148));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(0.130));
	ON_CALL(samples, getSample(4)).WillByDefault(Return(-0.1));
	ON_CALL(samples, getSample(5)).WillByDefault(Return(0.1));
	ON_CALL(samples, getSample(6)).WillByDefault(Return(-0.1));
	ON_CALL(samples, getSample(7)).WillByDefault(Return(0.1));
	ON_CALL(samples, getSample(8)).WillByDefault(Return(-0.1));
	ON_CALL(samples, getSample(9)).WillByDefault(Return(0.1));
	ZeroCrossingsProperty property(50, 100);

	//when
	int zeroCrossings = property.getValue(samples);

	//then
	ASSERT_EQ(zeroCrossings, 5);
}


