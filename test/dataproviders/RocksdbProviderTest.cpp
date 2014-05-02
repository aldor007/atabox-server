/*
 * RocksdbProviderTest.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: aldor
 */

#include "dataproviders/RocksdbProvider.h"
#include <string>
#ifndef GTEST_H_
	#define GTEST_H_
	#include "gtest/gtest.h"
#endif
class RocksdbProviderTest: public ::testing::Test {

};


TEST_F(RocksdbProviderTest, writeDataCanItRead) {
	std::string test = "test/file.db";

	RocksdbProvider<std::string, std::string> db(test);

	db.put("test", "value");
	std::string tmp = db.get("test");
	ASSERT_TRUE(tmp == "value");

}

TEST_F(RocksdbProviderTest, getListOfKeys) {
	std::string test = "test/file.db";

	RocksdbProvider<std::string, std::string> db(test);

	db.put("test2", "value");
	auto mapdata = db.getAllKV();

	ASSERT_TRUE(mapdata.size() >0);

}

