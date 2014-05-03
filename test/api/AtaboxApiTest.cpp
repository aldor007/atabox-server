#include "api/AtaboxApi.h"
#undef U
#include <string>
#ifndef GTEST_H_
	#define GTEST_H_
	#include "gtest/gtest.h"
#endif
class AtaboxApiTest: public ::testing::Test {

};


TEST_F(AtaboxApiTest, testAddMethod) {
	AtaboxApi test("http://localhost", "8888");
	handle_request_fun tmpFun;
	test.addMethod("test", tmpFun);
	std::map<utility::string_t, handle_request_fun> testMap;
	testMap = test.getMethods();
	auto result = testMap.find("test");
	ASSERT_TRUE(result != testMap.end());

}
