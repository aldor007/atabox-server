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
#include "wave/analysis/AverageValueProperty.h"

using ::testing::Return;

class AverageValuePropertyTest: public ::testing::Test {

};

TEST_F(AverageValuePropertyTest, returnCorrectValueOfPropertyForAllSamples) {
	//given
	SamplesMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(-0.12));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(-0.130));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.148));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(0.130));
	ON_CALL(samples, getSample(4)).WillByDefault(Return(-0.1));
	AverageValueProperty property;

	//when
	double result = property.getValue(samples);

	//then
	ASSERT_DOUBLE_EQ(result, 0.1256);
}

TEST_F(AverageValuePropertyTest, returnsCorrectNameForAllSamples) {
	//given
	AverageValueProperty property;

	//when
	string name = property.getName();

	//then
	ASSERT_STRCASEEQ("averageValue_from_0_to_100_percent", name.c_str());
}


TEST_F(AverageValuePropertyTest, returnCorrectValueOfPropertyForPartOfSamples) {
	//given
	SamplesMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(10));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(-0.1));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(-0.2));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.3));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(0.4));
	ON_CALL(samples, getSample(4)).WillByDefault(Return(-0.5));
	ON_CALL(samples, getSample(5)).WillByDefault(Return(-0.6));
	ON_CALL(samples, getSample(6)).WillByDefault(Return(-0.7));
	ON_CALL(samples, getSample(7)).WillByDefault(Return(-0.8));
	ON_CALL(samples, getSample(8)).WillByDefault(Return(-0.9));
	ON_CALL(samples, getSample(9)).WillByDefault(Return(-1.0));
	AverageValueProperty property(20, 30);

	//when
	double result = property.getValue(samples);

	//then
	ASSERT_NEAR(result, 0.35, 0.00001);
}


TEST_F(AverageValuePropertyTest, returnCorrectValueOfPropertyForPartOfSamples2) {
	//given
	SamplesMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(10));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(-0.1));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(-0.2));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.3));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(0.4));
	ON_CALL(samples, getSample(4)).WillByDefault(Return(-0.5));
	ON_CALL(samples, getSample(5)).WillByDefault(Return(-0.6));
	ON_CALL(samples, getSample(6)).WillByDefault(Return(-0.7));
	ON_CALL(samples, getSample(7)).WillByDefault(Return(-0.8));
	ON_CALL(samples, getSample(8)).WillByDefault(Return(-0.9));
	ON_CALL(samples, getSample(9)).WillByDefault(Return(-1.0));
	AverageValueProperty property(80, 100);

	//when
	double result = property.getValue(samples);

	//then
	ASSERT_NEAR(result, 0.9, 0.00001);
}

