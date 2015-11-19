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
#include "wave/analysis/WhereIsAmplitudeProperty.h"

using ::testing::Return;

class WhereIsAmplitudePropertyTest: public ::testing::Test {

};

TEST_F(WhereIsAmplitudePropertyTest, locatesMaximumCorrectly) {
	//given
	SamplesMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(0.128));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(-0.5)); // here is amplitude
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.16));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(0.130));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(0.10));
	WhereIsAmplitudeProperty property;

	//when
	double amplitude = property.getValue(samples);

	//then
	ASSERT_DOUBLE_EQ(amplitude, 25);
}

TEST_F(WhereIsAmplitudePropertyTest, returnsCorrectName) {
	//given
	WhereIsAmplitudeProperty property;

	//when
	std::string name = property.getName();

	//then
	ASSERT_STRCASEEQ("whereIsAmplitude", name.c_str());
}
