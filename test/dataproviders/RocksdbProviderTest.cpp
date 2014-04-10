/*
 * RocksdbProviderTest.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: aldor
 */

#include "dataproviders/RocksdbProvider.h"
#include "gtest/gtest.h"
#include <string>
class RocksdbProviderTest: public ::testing::Test {

};


TEST_F(RocksdbProviderTest, writeDataCanItRead) {
	std::string test = "test/file.db";

	RocksdbProvider<std::string, std::string> db(test);

	db.set("test", "value");
	std::string tmp = db.get("test");
	ASSERT_TRUE(tmp == "value");

}
