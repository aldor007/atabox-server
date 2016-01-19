//
// Created by aldor on 19.01.16.
//
#undef U
#ifndef GTEST_H_
#define GTEST_H_

#include <wave/WaveFile.h>
#include <recognition/FeatureExtractor.h>

#include <iostream>
#include <recognition/network/DBN.h>

#undef U
#include "gtest/gtest.h"
#endif

class DBNTest: public ::testing::Test {

};
/*
TEST_F(DBNTest, testFeauteExraction) {

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

    DBN dbn(500, {1000, 1000, 100}, 10);

    // read data from file pretrain network
    dbn.init();
    shark::RealVector result = dbn.getOutput();

    ASSERT_NEAR(0.0707306, result[0], 0.001);
    ASSERT_NEAR(-0.0662722, result[1], 0.001);
    ASSERT_NEAR(-0.0891499, result[2], 0.001);
}
*/