/*
 * RVMTest.cpp
 *
 *  Created on: 04.10.2015
 *      Author: aldor
 */


#include "recognition/network/RBM.h"

#undef U
#ifndef GTEST_H_
#define GTEST_H_
#include "gtest/gtest.h"
#endif
class RBMTest: public ::testing::Test {

};

// check whether it throws some exception
TEST_F(RBMTest, testDefualData) {
    // use rbm with default config
    RBM::Config config;
    RBM rbm{config};
}

