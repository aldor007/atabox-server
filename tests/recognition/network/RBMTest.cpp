/*
 * RVMTest.cpp
 *
 *  Created on: 04.10.2015
 *      Author: aldor
 */



#undef U
#ifndef GTEST_H_
#define GTEST_H_

#include <recognition/network/RBM.h>
#include <wave/WaveFile.h>
#include <recognition/FeatureExtractor.h>

#include <iostream>
#include <wave/analysis/MfccProperty.h>

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

    RBM::Config config;
    config.numberOfHidden = 3;
    config.numberOfVisible = propArr[0].as_object().at(MfccProperty::NAME).size() + propArr[0].as_object().size();
    config.batchSize = 1;

    RBM rbm{config};
    rbm.train(propArr);

    shark::RealVector result = rbm.getHiddenLaverParameters();
    // TODO: check tests
    ASSERT_EQ(3, result.size());
    ASSERT_NEAR(-0.12666124345209478, result[0], 0.001);
    ASSERT_NEAR(0.10972186203454415, result[1], 0.001);
    ASSERT_NEAR(-0.098557418239849343, result[2], 0.001);

}

