
#include "utils/jsonextend.h"
#include <map>

#undef U
#ifndef GTEST_H_
	#define GTEST_H_
	#include "gtest/gtest.h"
#endif
class jsonextendTest: public ::testing::Test {

};


TEST_F(jsonextendTest, create) {

	jsonextend value;
     value["test"] = web::json::value::string("a");
     ASSERT_EQ(value["test"].as_string(), "a");
}

TEST_F(jsonextendTest, castToString) {

	jsonextend value;
     value["test"] = web::json::value::string("a");
     std::string test = static_cast<std::string>(value);
     ASSERT_EQ(test, std::string("{\"test\":\"a\"}"));
}

TEST_F(jsonextendTest, createfromstring) {
    std::string testS("{\"test\":\"a\"}");
	jsonextend value(testS);
     value["test"] = web::json::value::string("a");

     ASSERT_EQ(value["test"].as_string(), "a");
}
TEST_F(jsonextendTest, storeinmap) {
	jsonextend value;
     value["test"] = web::json::value::string("a");
     std::map<jsonextend, std::string> testowa;
     testowa[value] = "ala";

     //ASSERT_STREQ(testowa[value].c_str(), "ala");
}
TEST_F(jsonextendTest, testoperatoraddeq) {
	jsonextend value;
     value["test"] = web::json::value::string(std::string("a"));
     jsonextend value1;
     value1["tomek"] = web::json::value::string(std::string("karolina"));
     value1 += value;
     ASSERT_TRUE(value1.has_field("tomek"));
     ASSERT_EQ(value1["test"].as_string(), "a");
     ASSERT_EQ(value1["tomek"].as_string(), "karolina");
}
TEST_F(jsonextendTest, testoperatoradd) {
	jsonextend value;
     value["test"] = web::json::value::string(std::string("a"));
     jsonextend value1;
     value1["tomek"] = web::json::value::string(std::string("karolina"));
     jsonextend result = value1 + value;
     ASSERT_TRUE(result.has_field("tomek"));
     ASSERT_EQ(result["tomek"].as_string(), "karolina");
     ASSERT_TRUE(result.has_field("test"));
     ASSERT_EQ(result["test"].as_string(), "a");
}

TEST_F(jsonextendTest, throwExectpionWhenWrongJSON) {

	std::string propString = std::string("{\"ampltude\":null,name\":\"nowa\",\"percentageAbove10percentage\":0,\"percentageAbove20percentage\":0,") +
			std::string("\"percentageAbove30percentage\":0,\"percentageAbove40percentage\":0,\"percentageAbove50percentage\":0,\"percentageAbove60percentage\":0,") +
			std::string("\"percentageAbove70percentage\":0,\"percentageAbove80percentage\":0,\"percentageAbove90percentage\":0,\"zeroCrossings\":1185}");
ASSERT_THROW(jsonextend(propString).serialize(), web::json::json_exception);


}
