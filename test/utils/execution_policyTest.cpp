#include <map>
#include <string>

#include <wave/analysis/WaveProperties.h>
#include <recognition/PropertiesComparator.h>

#include <boost/log/trivial.hpp>
#include <utils/execution_policy.h>
#undef U
#ifndef GTEST_H_
	#define GTEST_H_
	#include "gtest/gtest.h"
#endif
class execution_policyTest: public ::testing::Test {

};


TEST_F(execution_policyTest, strictFound) {
	std::map<WaveProperties, std::string> testMap;
	WaveProperties prop1;
	prop1.amplitude = 1;
	WaveProperties prop2;
	prop2.amplitude = 3434;

	WaveProperties given;
	given.amplitude = 1;
	testMap[prop1] = "jeden";
	testMap[prop2] = "dwa";
	std::string result = execution_policy_strict(testMap, prop1);
	ASSERT_EQ(result, testMap[prop1]);
}
TEST_F(execution_policyTest, strictNotFound) {
	std::map<WaveProperties, std::string> testMap;
	WaveProperties prop1;
	prop1.amplitude = 1;
	WaveProperties prop2;
	prop2.amplitude = 3434;

	WaveProperties given;
	given.amplitude = 3;
	testMap[prop1] = "jeden";
	testMap[prop2] = "dwa";
	std::string result = execution_policy_strict(testMap, given);
	ASSERT_EQ(result, std::string());
}
TEST_F(execution_policyTest, nonstrictFound) {
	std::map<WaveProperties, std::string> testMap;
	WaveProperties prop1;
	prop1.amplitude = 1;
	WaveProperties prop2;
	prop2.amplitude = 3434;

	WaveProperties given;
	given.amplitude = 2;
	testMap[prop1] = "jeden";
	testMap[prop2] = "dwa";
	std::string result = execution_policy_nonstrict(testMap, given);
	ASSERT_EQ(result, testMap[prop1]);
}
