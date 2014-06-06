/*
 * WaveProperties_test.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "wave/analysis/WaveProperties.h"
#include "cpprest/json.h"
#undef U
#include "gtest/gtest.h"

class WavePropertiesTest: public ::testing::Test {

};

TEST_F(WavePropertiesTest, canCreateFromJSONString) {
	WaveProperties tmp;
	tmp.amplitude = 0.5;
	tmp.name = "nowa";
	std::string propString = tmp.toString();
/*std::string propString = std::string("{\"amplitude\":0.5,\"name\":\"nowa\",\"percentageAbove10percentage\":0,\"percentageAbove20percentage\":0,") +
			std::string("\"percentageAbove30percentage\":0,\"percentageAbove40percentage\":0,\"percentageAbove50percentage\":0,\"percentageAbove60percentage\":0,") +
			std::string("\"percentageAbove70percentage\":0,\"percentageAbove80percentage\":0,\"percentageAbove90percentage\":0,\"zeroCrossings\":1185}");
*/
WaveProperties test(propString);
	ASSERT_EQ(test.name, "nowa");
	ASSERT_EQ(test.amplitude, 0.5);

}
TEST_F(WavePropertiesTest, throwExectpionWhenWrongJSON) {

	std::string propString = std::string("{\"ampltude\":null,\"name\":\"nowa\",\"percentageAbove10percentage\":0,\"percentageAbove20percentage\":0,") +
			std::string("\"percentageAbove30percentage\":0,\"percentageAbove40percentage\":0,\"percentageAbove50percentage\":0,\"percentageAbove60percentage\":0,") +
			std::string("\"percentageAbove70percentage\":0,\"percentageAbove80percentage\":0,\"percentageAbove90percentage\":0,\"zeroCrossings\":1185}");
	int counter = 0;
//ASSERT_THROWyy(WaveProperties test(propString), web::json::json_exception);
	try {

  WaveProperties test(propString);
	} catch(web::json::json_exception &e) {
		counter++;
	}
	ASSERT_EQ(counter, 1);


}
TEST_F(WavePropertiesTest, toStringWorksProperly) {

	std::string propString = std::string("{\"amplitude\":0.5,\"lengthInSeconds\":80,\"name\":\"nowa\",\"percentageAbove10percentage\":0,\"percentageAbove20percentage\":0,") +
			std::string("\"percentageAbove30percentage\":0,\"percentageAbove40percentage\":0,\"percentageAbove50percentage\":0,\"percentageAbove60percentage\":0,") +
			std::string("\"percentageAbove70percentage\":0,\"percentageAbove80percentage\":0,\"percentageAbove90percentage\":0,\"zeroCrossings\":1185}");

  WaveProperties test(propString);
 ASSERT_EQ(test.toString(), propString);

}
TEST_F(WavePropertiesTest, canCastToString) {

	std::string propString = std::string("{\"amplitude\":0.5,\"lengthInSeconds\":80,\"name\":\"nowa\",\"percentageAbove10percentage\":0,\"percentageAbove20percentage\":0,") +
			std::string("\"percentageAbove30percentage\":0,\"percentageAbove40percentage\":0,\"percentageAbove50percentage\":0,\"percentageAbove60percentage\":0,") +
			std::string("\"percentageAbove70percentage\":0,\"percentageAbove80percentage\":0,\"percentageAbove90percentage\":0,\"zeroCrossings\":1185}");

  WaveProperties test(propString);
 ASSERT_EQ(static_cast<std::string>(test), propString);

}
