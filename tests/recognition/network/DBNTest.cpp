//
// Created by aldor on 19.01.16.
//
#undef U
#ifndef GTEST_H_
#define GTEST_H_

#include <wave/WaveFile.h>
#include "recognition/FeatureExtractor.h"

#include <iostream>
#include <recognition/network/DBN.h>
#include <wave/analysis/MfccProperty.h>
#include <utils/functions.h>

#undef U
#include "gtest/gtest.h"
#endif

class DBNTest: public ::testing::Test {

};
//TEST_F(DBNTest, DISABLED_testRawData) {
//
//    const int size = 200;
//    const int sampleSize = 2500;
//    std::valarray<shark::RealVector> norm{size};
//
//    RBMConfig config;
//    config.numberOfTrails = 2;
//    config.numberOfIteration = 1000;
//    config.batchSize = size;
//    config.learningRate = 0.01;
//    for (int i = 0; i < size; ++i) {
//        norm[i].reserve(sampleSize);
//        for (int j = 0; j < sampleSize; ++j) {
//            norm[i].push_back(j * ((i + 1)/ 1000.));
//        }
//    }
//
//
//    DBN dbn(sampleSize, {10}, 3, config);
////    dbn.init("/Users/aldor/workspace/atabox-server/dbn.arch");
//    dbn.train(norm);
//    //dbn.store();
//
//    shark::RealVector test;
//    test.reserve(sampleSize);
//    for (int j = 0; j < sampleSize; ++j) {
//        test.push_back(-1/1000000.1);
//    }
//
//    shark::RealVector result = dbn.predict(test);
//
//    std::cout << "DBN result new " << std::endl;
//    for (auto it : result) {
//        std::cout << it  << std::endl;
//    }
//
//    shark::RealVector result2 = dbn.predict(norm[1]);
//
//    std::cout << "DBN result trained" << std::endl;
//    for (auto it : result2) {
//        std::cout << it  << std::endl;
//    }
//
//    shark::RealVector result1 = dbn.predict(norm[0]);
//
//
//    std::cout << "DBN result trained" << std::endl;
//    for (auto it : result1) {
//        std::cout << it  << std::endl;
//    }
//
//}
//
//TEST_F(DBNTest, DISABLED_testSmallSamples_wave) {
//
//    WaveFile waves[] = {
//            WaveFile("./tests/wave/waveFiles/dziendobryMarcin1.wav"),
//            WaveFile("./tests/wave/waveFiles/dzienDobryTata1.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryTomek-01.wav")};
//
//    const int size = 3;
//    Samples samples[size];
//    std::valarray<jsonextend> propArr(size);
//    std::valarray<shark::RealVector> norm(size);
//    FeatureExtractor extractor;
//    extractor.init();
//    for (uint16_t i = 0; i < size; ++i) {
//        samples[i] = Samples(waves[i]);
//        propArr[i] = extractor.getSummary(samples[i]);
//    }
//
//    RBMConfig config;
//    config.numberOfTrails = 2;
//    config.numberOfIteration = 1000;
//    config.batchSize = size;
//
//    for (uint16_t i = 0; i < size; ++i) {
////        norm[i++] = std::move(val.toRealVector());
//        norm[i] = extractor.getSummaryRealVector(samples[i]);
//    }
//
////    size_t max = normalizeArray<std::valarray<shark::RealVector>, shark::RealVector>(norm);
//    uint16_t input = norm[0].size();
//    DBN dbn(input, {100, 10}, 3, config);
////    dbn.init("/Users/aldor/workspace/atabox-server/dbn.arch");
//    dbn.train(norm);
//    dbn.store();
//
//    Samples s{WaveFile("./tests/wave/waveFiles/dziendobryBabcia.wav")};
//    jsonextend sj = extractor.getSummary(s);
//    shark::RealVector normSJ = extractor.getSummaryRealVector(s);
////    normalize(normSJ);
////    std::cout << "size norm = " << norm[0].size() << " max = " << max << " normsj " << normSJ.size() << "\n";
//    for (size_t j = 0; j < norm.size(); ++j) {
//        std::cout << "norm = " << norm[0][j] << " babcia = " << normSJ[j] << std::endl;
//    }
//
//    shark::RealVector result = dbn.predict(normSJ);
//
//    std::cout << "DBN result new " << std::endl;
//    for (auto it : result) {
//        std::cout << it  << std::endl;
//    }
//
//    shark::RealVector result2 = dbn.predict(norm[1]);
//
//    std::cout << "DBN result trained" << std::endl;
//    for (auto it : result2) {
//        std::cout << it  << std::endl;
//    }
//
//}
//
//TEST_F(DBNTest, DISABLED_testFeauteExraction) {
//
//    WaveFile waves[] = {
//            WaveFile("./tests/wave/waveFiles/dziendobryMarcin1.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryMarcin2.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryMarcin3.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryMarcin4.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryMarcin5.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryMarcin6.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryMarcin7.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryMarcin8.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryMarcin9.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryMarcin10.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryMarcin1.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryMarcin12.wav"),
//            WaveFile("./tests/wave/waveFiles/dzienDobryTata1.wav"),
//            WaveFile("./tests/wave/waveFiles/dzienDobryTata2.wav"),
//            WaveFile("./tests/wave/waveFiles/dzienDobryTata3.wav"),
//            WaveFile("./tests/wave/waveFiles/dzienDobryTata4.wav"),
//            WaveFile("./tests/wave/waveFiles/dzienDobryTata5.wav"),
//            WaveFile("./tests/wave/waveFiles/dzienDobryTata6.wav"),
//            WaveFile("./tests/wave/waveFiles/dzienDobryTata7.wav"),
//            WaveFile("./tests/wave/waveFiles/dzienDobryTata8.wav"),
//            WaveFile("./tests/wave/waveFiles/dzienDobryTata9.wav"),
//            WaveFile("./tests/wave/waveFiles/dzienDobryTata10.wav"),
//            WaveFile("./tests/wave/waveFiles/dzienDobryTata11.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryTomek-01.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryTomek-02.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryTomek-03.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryTomek-04.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryTomek-05.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryTomek-06.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryTomek-07.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryTomek-08.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryTomek-09.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryTomek-10.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryTomek-11.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryTomek-12.wav"),
//            WaveFile("./tests/wave/waveFiles/dziendobryTomek-13.wav")};
//
//    const int size = 35;
//    Samples samples[size];
//    std::valarray<jsonextend> propArr(size);
//    std::valarray<shark::RealVector> norm(size);
//    FeatureExtractor extractor;
//    extractor.init();
//    for (uint16_t i = 0; i < size; ++i) {
//        samples[i] = Samples(waves[i]);
//        propArr[i] = extractor.getSummary(samples[i]);
//    }
//    propArr[0].saveToFile("/tmp/dziendobryMarcin.json");
//    propArr[33].saveToFile("/tmp/dziendobryTomek.json");
//    propArr[18].saveToFile("/tmp/dziendobryTata.json");
//    std::cout << "Length in seconds: " << samples[0].getLenghtInSeconds() << " " << samples[18].getLenghtInSeconds() << " " <<
//    samples[33].getLenghtInSeconds() << std::endl;
//    std::cout << " Samples: " << samples[0].getNumberOfSamples() << " " << samples[18].getNumberOfSamples() << " " <<
//    samples[33].getNumberOfSamples() << std::endl;
//    RBMConfig config;
//    config.numberOfTrails = 2;
//    config.numberOfIteration = 1000;
//    config.batchSize = size;
//
//    for (uint16_t i = 0; i < size; ++i) {
////        norm[i++] = std::move(val.toRealVector());
//        norm[i] = extractor.getSummaryRealVector(samples[i]);
//    }
//
////    size_t max = normalizeArray<std::valarray<shark::RealVector>, shark::RealVector>(norm);
//    uint16_t input = norm[0].size();
//    DBN dbn(input, {1000, 100, 10}, 3, config);
////    dbn.init("/Users/aldor/workspace/atabox-server/dbn.arch");
//    dbn.train(norm);
//    dbn.store();
//
//    Samples s{WaveFile("./tests/wave/waveFiles/dziendobryBabcia.wav")};
//    jsonextend sj = extractor.getSummary(s);
//    shark::RealVector normSJ = extractor.getSummaryRealVector(s);
//   // normalize(normSJ, max);
//    std::cout << "size norm = " << norm[0].size() << " max = " << max << " normsj " << normSJ.size() << "\n";
//    for (size_t j = 0; j < norm.size(); ++j) {
//        std::cout << "norm = " << norm[0][j] << " babcia = " << normSJ[j] << std::endl;
//    }
//
//    shark::RealVector result = dbn.predict(normSJ);
//
//    std::cout << "DBN result new " << std::endl;
//    for (auto it : result) {
//        std::cout << it  << std::endl;
//    }
//
//    propArr[0].saveToFile("/tmp/prop0.json");
//    shark::RealVector result2 = dbn.predict(norm[1]);
//
//    std::cout << "DBN result trained" << std::endl;
//    for (auto it : result2) {
//        std::cout << it  << std::endl;
//    }
//
//}
