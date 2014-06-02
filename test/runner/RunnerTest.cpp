#include <runner/Runner.h>
#undef U
#ifndef GTEST_H_
	#define GTEST_H_
	#include "gtest/gtest.h"
#endif
class RunnerTest: public ::testing::Test {

};


TEST_F(RunnerTest, run_command_no_path_no_args) {
	web::json::value result = Runner::run("pwd", "");
	ASSERT_TRUE(result["cmd_status"].as_string() == "RUN");
	ASSERT_EQ(result["cmd_code"].as_integer(), 0);
}

TEST_F(RunnerTest, run_command_path_no_args) {
	Runner runTest();
	web::json::value result = Runner::run("/bin/ls");
	ASSERT_TRUE(result["cmd_status"].as_string() == "RUN");
	ASSERT_EQ(result["cmd_code"].as_integer(), 0);
}

TEST_F(RunnerTest, run_command_path_args) {
	Runner runTest();
	web::json::value result = Runner::run("/bin/ls", "-l");
	ASSERT_TRUE(result["cmd_status"].as_string() == "RUN");
	ASSERT_EQ(result["cmd_code"].as_integer(), 0);
}
TEST_F(RunnerTest, notCommandPathArgs) {
	Runner runTest();
	web::json::value result = Runner::run("/bin/lsa", "-l");
	ASSERT_TRUE(result["cmd_status"].as_string() == "ERROR");
	ASSERT_NE(result["cmd_code"].as_integer(), 0);
}

TEST_F(RunnerTest, notCommandNoPathArgs) {
	Runner runTest();
	web::json::value result = Runner::run("lsa", "-l");
	ASSERT_TRUE(result["cmd_status"].as_string() == "ERROR");
	ASSERT_NE(result["cmd_code"].as_integer(), 0);
}

TEST_F(RunnerTest, commandErrorRun) {
	Runner runTest();
	web::json::value result = Runner::run("pwd", "-jiq");
	ASSERT_TRUE(result["cmd_status"].as_string() == "RUN");
	ASSERT_NE(result["cmd_code"].as_integer(), 0);
}
