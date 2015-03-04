#include <map>
#include <string>

#include "recognition/PropertiesComparator.h"

#include <boost/log/trivial.hpp>
#include "utils/execution_policy.h"
#undef U
#ifndef GTEST_H_
	#define GTEST_H_
	#include "gtest/gtest.h"
#endif
class execution_policyTest: public ::testing::Test {

};


TEST_F(execution_policyTest, strictFound) {
	std::map<jsonextend, std::string> testMap;
	jsonextend prop1;
	prop1["amplitude"] = web::json::value::number(1);

	jsonextend prop2;
	prop2["amplitude"] = web::json::value::number(2222);

	jsonextend given;
	given["amplitude"] = web::json::value::number(1);
	testMap[prop1] = "jeden";
	testMap[prop2] = "dwa";
	std::string result = execution_policy_strict(testMap, prop1);
	ASSERT_EQ(result, testMap[prop1]);
}
TEST_F(execution_policyTest, strictNotFound) {
	std::map<jsonextend, std::string> testMap;
	jsonextend prop1;
	prop1["amplitude"] = web::json::value::number(1);

	jsonextend prop2;
	prop2["amplitude"] = web::json::value::number(2222);

	jsonextend given;
	given["amplitude"] = web::json::value::number(2);
	testMap[prop1] = "jeden";
	testMap[prop2] = "dwa";
	std::string result = execution_policy_strict(testMap, given);
	ASSERT_EQ(result, std::string());
}
TEST_F(execution_policyTest, nonstrictFound) {
	std::map<jsonextend, std::string> testMap;
	jsonextend prop1;
	prop1["amplitude"] = web::json::value::number(1);

	jsonextend prop2;
	prop2["amplitude"] = web::json::value::number(2222);

	jsonextend given;
	given["amplitude"] = web::json::value::number(2);
	testMap[prop1] = "jeden";
	testMap[prop2] = "dwa";
	std::string result = execution_policy_nonstrict(testMap, given);
	ASSERT_EQ(result, testMap[prop1]);
}
