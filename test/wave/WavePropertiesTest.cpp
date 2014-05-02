/*
 * WaveProperties_test.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "wave/WaveProperties.h"
#undef U
#include "gtest/gtest.h"

class WavePropertiesTest: public ::testing::Test {

};

TEST_F(WavePropertiesTest, canCreateFromJSONString) {
	std::string propString = std::string("\"{amplitude\":0.5,\"name\":\"nowaaaa\",\"percentageAbove10percentage\":0,\"percentageAbove20percentage\":0,") +
			std::string("\"percentageAbove30percentage\":0,\"percentageAbove40percentage\":0,\"percentageAbove50percentage\":0,\"percentageAbove60percentage\":0,") +
			std::string("\"percentageAbove70percentage\":0,\"percentageAbove80percentage\":0,\"percentageAbove90percentage\":0,\"zeroCrossings\":1185}");
	WaveProperties test(propString);
	ASSERT_EQ(test.name, "nowaaa");
	ASSERT_EQ(test.amplitude, 0.5);

}
