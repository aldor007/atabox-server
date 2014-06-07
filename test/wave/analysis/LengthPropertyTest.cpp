/*
 * LengthPropertyTest.cpp
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SamplesMock.h"
#include "wave/analysis/LengthProperty.h"

using ::testing::Return;

class LengthPropertyTest: public ::testing::Test {

};

TEST_F(LengthPropertyTest, returnCorrectValueOfProperty) {
	SamplesMock samples;
	//given
	ON_CALL(samples, getLenghtInSeconds()).WillByDefault(Return(4.5));
	LengthProperty property;
	//when
	double value = property.getValue(samples);
	//then
	ASSERT_DOUBLE_EQ(value, 4.5);
}
