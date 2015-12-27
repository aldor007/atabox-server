/*
 * RVMTest.cpp
 *
 *  Created on: 04.10.2015
 *      Author: aldor
 */


//#include "AtaboxRBM.h"

#undef U
#ifndef GTEST_H_
#define GTEST_H_

#include <recognition/network/RBM.h>
#include <wave/WaveFile.h>
#include <recognition/FeatureExtractor.h>

#include <iostream>

#undef U
#include "gtest/gtest.h"
#endif
class RBMTest: public ::testing::Test {

};

// check whether it throws some exception
TEST_F(RBMTest, testFeauteExraction) {

    WaveFile waves[] = {
            WaveFile("./tests/wave/waveFiles/dziekuje32bit.wav"),
            WaveFile("./tests/wave/waveFiles/dziekuje32bit.wav"),
            WaveFile("./tests/wave/waveFiles/dziekuje32bit.wav")};
//                         WaveFile("./tests/wave/waveFiles/ping32bit_1.wav"),
//                         WaveFile("./tests/wave/waveFiles/ping32bit_1.wav"),
//                         WaveFile("./tests/wave/waveFiles/ping32bit_1.wav")};
//                         WaveFile("./tests/wave/waveFiles/vim32bit_1.wav")};
    Samples samples[3];
    std::valarray<jsonextend> propArr(3);
    FeatureExtractor extractor;
    extractor.init();
    for (uint16_t i = 0; i < 3; ++i) {
        samples[i] = Samples(waves[i]);
        propArr[i] = extractor.getSummary(samples[i]);
    }

    RBM rbm{propArr, 3};
    rbm.setData(propArr);
    rbm.learn();
//    for (auto value:   rbm.getHiddenLaverParameters()) {
//        std::cout<<value<<std::endl;
//
//    }
    shark::RealVector result = rbm.getHiddenLaverParameters();

    ASSERT_NEAR(0.0707306, result[0], 0.001);
    ASSERT_NEAR(-0.0662722, result[1], 0.001);
    ASSERT_NEAR(-0.0891499, result[2], 0.001);
}

