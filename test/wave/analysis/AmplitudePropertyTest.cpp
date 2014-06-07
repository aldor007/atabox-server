/*
 * AmplitudePropertyTest.cpp
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SamplesMock.h"
#include "wave/analysis/AmplitudeProperty.h"

using ::testing::Return;

class AmplitudePropertyTest: public ::testing::Test {

};

TEST_F(AmplitudePropertyTest, findsMaximumCorrectly) {
	//given
	SamplesMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(4));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(0.128));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(-0.5));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.16));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(0.130));
	AmplitudeProperty property;

	//when
	double amplitude = property.getValue(samples);

	//then
	ASSERT_DOUBLE_EQ(amplitude, 0.5);
}

TEST_F(AmplitudePropertyTest, returnsCorrectName) {
	//given
	AmplitudeProperty property;

	//when
	string name = property.getName();

	//then
	ASSERT_STRCASEEQ("amplitude", name.c_str());
}
