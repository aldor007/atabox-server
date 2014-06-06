/*
 * RocksdbProviderTest.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: aldor
 */

#include "dataproviders/RocksdbProvider.h"
#include "wave/analysis/WaveProperties.h"
#undef U
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

TEST_F(RocksdbProviderTest, putAndGetWaveProperies) {
	std::string dbname = "test/file.db";

	RocksdbProvider<WaveProperties, std::string> db(dbname);
	WaveProperties test;
	test.name ="vim";
	test.amplitude = 0.2;
	std::string expected = "vim /tmp/test";
	db.put(test, expected);
	ASSERT_EQ(db.get(test), expected);


}

