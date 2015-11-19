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
	//given
	SamplesMock samples;
	ON_CALL(samples, getLenghtInSeconds()).WillByDefault(Return(4.5));
	LengthProperty property;
	//when

	double value = samples.getLenghtInSeconds();
			//property.getValue(samples);
	//then
	ASSERT_DOUBLE_EQ(value, 4.5);
}


TEST_F(LengthPropertyTest, returnsCorrectName) {
	//given
	LengthProperty property;

	//when
	std::string name = property.getName();

	//then
	ASSERT_STRCASEEQ("length", name.c_str());
}
