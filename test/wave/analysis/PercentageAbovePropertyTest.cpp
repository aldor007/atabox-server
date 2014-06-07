/*
 * PercentageAbovePropertyTest.cpp
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SamplesMock.h"
#include "wave/analysis/PercentageAboveProperty.h"

using ::testing::Return;

class PercentageAbovePropertyTest: public ::testing::Test {

};

TEST_F(PercentageAbovePropertyTest, returnCorrectValue) {
	//given
	SamplesMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(-0.11));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(0.7));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.2));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(1));
	ON_CALL(samples, getSample(4)).WillByDefault(Return(-1));

	PercentageAboveProperty property(0.5);

	//when
	double percentageAbove = property.getValue(samples);

	//then
	ASSERT_DOUBLE_EQ(percentageAbove, 3.0 / 5.0);
}

TEST_F(PercentageAbovePropertyTest, returnsCorrectName) {
	//given
	PercentageAboveProperty property(0.3);

	//when
	string name = property.getName();

	//then
	ASSERT_STRCASEEQ("percentageAbove_0.3", name.c_str());
}
