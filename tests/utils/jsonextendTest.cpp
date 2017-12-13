
#include "utils/jsonextend.h"
#include <map>
#include <wave/Samples.h>
#include "recognition/FeatureExtractor.h"

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

TEST_F(jsonextendTest, test_to_RealVector) {
    std::vector<web::json::value> data;
    data.push_back(web::json::value::number(2.1));
    jsonextend value;
    value["mfcc"] = web::json::value::array(data);
    value["mmamp"] = web::json::value::number(3.3);
    shark::RealVector convert = value.toRealVector();

    ASSERT_EQ(convert[0], 2.1);
    ASSERT_EQ(convert[1], 3.3);
}

TEST_F(jsonextendTest, createFromVectorOfVectors) {

    std::vector<std::vector<double>> data{{1., 2., 4.}, {1, 2, 3}};
    jsonextend json(data);
    std::vector<std::vector<double>> converted = static_cast<std::vector<std::vector<double>>>(json);

    ASSERT_EQ(data.size(), converted.size());
    for (int i = 0, len = data.size(); i < len; ++i) {
        for (int j = 0, inLen = data[i].size(); j < len; ++j) {
            ASSERT_EQ(converted[i][j], data[i][j]);
        }
    }
}

TEST_F(jsonextendTest, DISABLED_test_to_RealVector2) {
    FeatureExtractor extractor;
    extractor.init();
    Samples s{WaveFile{"./tests/wave/waveFiles/dziendobryMarcin1.wav"}};
    jsonextend value = extractor.getSummary(s);
    shark::RealVector rv = value.toRealVector();
    shark::RealVector rv2 = value.toRealVector();

    ASSERT_EQ(rv.size(), rv2.size());
    size_t i = 0;
    for (auto iter = value.as_object().cbegin(); iter != value.as_object().cend(); ++iter) {

        if (iter->first == "mfcc") {
            for (auto mfcc: iter->second.as_array()) {
                ASSERT_EQ(mfcc.as_double(), rv[i++]);
            }

        } else  {
            if (iter->second.is_double())
                ASSERT_EQ(iter->second.as_double(), rv[i]);
            else if (iter->second.is_integer())
                ASSERT_EQ(iter->second.as_integer(), rv[i]);
            i++;
        }
    }
}
