/*
 * RocksdbProviderTest.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: aldor
 */

#include "dataproviders/RocksdbProvider.h"
#include "utils/jsonextend.h"

#undef U
#include <string>
#ifndef GTEST_H_
    #define GTEST_H_
    #include "gtest/gtest.h"
#endif
class RocksdbProviderTest: public ::testing::Test {

};


TEST_F(RocksdbProviderTest, writeDataCanItRead) {
    std::string test = "tests/file.db";

    RocksdbProvider<std::string, std::string> db(test);

    db.put("test", "value");
    std::string tmp;
    db.get("test", tmp);
    ASSERT_TRUE(tmp == "value");

}

TEST_F(RocksdbProviderTest, writeDataCanItReadVector) {
    std::string test = "tests/file.db";

    RocksdbProvider<std::string, std::vector<double>> db(test);
    std::vector<double> v{2., 12.3, 33};

    db.put("testV", v);
    std::vector<double> r;
    db.get("testV", r);
    for (int i = 0; i < v.size(); ++i) {
        ASSERT_TRUE(v[i] == r[i]);
    }

}


TEST_F(RocksdbProviderTest, writeDataCanItReadVectorOfVector) {
    std::string test = "tests/file.db";

    RocksdbProvider<std::string, std::vector<std::vector<double>>> db(test);
    std::vector<std::vector<double>> v{{2., 12.3, 33}, {1, 1,1}};

    db.put("testV22", v);
    std::vector<std::vector<double>> r;
    db.get("testV22", r);
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[i].size(); ++j) {
            ASSERT_TRUE(v[i][j] == r[i][j]);
        }
    }

}

TEST_F(RocksdbProviderTest, getListOfKeys) {
    std::string test = "tests/file.db";

    RocksdbProvider<std::string, std::string> db(test);

    db.put("test2", "value");
    auto mapdata = db.getAllKV();

    ASSERT_TRUE(mapdata.size() >0);

}

TEST_F(RocksdbProviderTest, putAndGetWaveProperies) {
    std::string dbname = "tests/file.db";

    RocksdbProvider<jsonextend, std::string> db(dbname);
    jsonextend test;
    test["name"] = web::json::value::string("vim");
    test["amplitude"] = web::json::value::number(0.2);
    std::string expected = "vim /tmp/test";
    std::string tmp;
    db.put(test, expected);
    db.get(test, tmp);
    ASSERT_EQ(tmp, expected);
}

