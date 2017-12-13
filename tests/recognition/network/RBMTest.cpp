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
#include "recognition/FeatureExtractor.h"

#include <iostream>
#include <wave/analysis/MfccProperty.h>
#include <utils/functions.h>
#include <wave/processing/Spectrogram.h>

#undef U
#include "gtest/gtest.h"
#endif
//class RBMTest: public ::testing::Test {
//
//};
//
//TEST_F(RBMTest, DISABLED_testSpectogram) {
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
//    Spectrogram spec[size];
//    std::vector<shark::RealVector> data;
//
//    for (uint16_t i = 0; i < size; ++i) {
//        samples[i] = Samples(waves[i]);
//        spec[i] = Spectrogram(samples[i]);
//        data.push_back(spec[i].getData());
//    }
//
//    RBMConfig config;
//    config.numberOfTrails = 8;
//    config.numberOfIteration = 12000;
//    config.batchSize = 10;
//    config.numberOfHidden = 3;
//    config.learningRate = 0.2;
//
//    config.numberOfVisible = 20000;
//    RBM<shark::BinaryRBM, shark::BinaryPCD> rbm{config};
//    // rbm.init("/tmp/rbm.arch");
//    rbm.train(data);
//    // rbm.store();
//
//    Samples s{WaveFile("./tests/wave/waveFiles/dziendobryBabcia.wav")};
//    Spectrogram sBabcia{s};
//    shark::RealVector result = rbm.predict(sBabcia.getData());
//
//    std::cout << "DBN result new " << std::endl;
//    for (auto it : result) {
//        std::cout << it  << std::endl;
//    }
//
//    shark::RealVector result2 = rbm.predict(spec[2].getData());
//
//    std::cout << "DBN result trained" << std::endl;
//    for (auto it : result2) {
//        std::cout << it  << std::endl;
//    }
//
//
//}
//
//TEST_F(RBMTest, DISABLED_testSmallSamples_wave12) {
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
//    const int size = 3;
//    Samples samples[size];
//    std::valarray<shark::RealVector> norm(size);
//    FeatureExtractor extractor;
//    extractor.init();
//    for (uint16_t i = 0; i < size; ++i) {
//        samples[i] = Samples(waves[i]);
//    }
//
//    RBMConfig config;
//    config.numberOfTrails = 3;
//    config.numberOfIteration = 1000;
//    config.batchSize = 100;
//    config.numberOfHidden = 3;
//    config.learningRate = 0.001;
//    config.momentum = 0;
//
//
//    for (uint16_t i = 0; i < size; ++i) {
////        norm[i++] = std::move(val.toRealVector());
//        norm[i] = extractor.getSummaryRealVector(samples[i]);
//    }
//
////    size_t max = normalizeArray<std::valarray<shark::RealVector>, shark::RealVector>(norm);
//    //config.numberOfVisible = max;
//    std::cout << "---------------------TRAIN--------";
//    RBM<shark::GaussianBinaryRBM, shark::GaussianBinaryCD> rbm{config};
//    //rbm.init("/tmp/rbm.arch");
//    rbm.train(norm);
//    rbm.store();
//
//    Samples s{WaveFile("./tests/wave/waveFiles/dziendobryBabcia.wav")};
//    jsonextend sj = extractor.getSummary(s);
//    shark::RealVector normSJ = extractor.getSummaryRealVector(s);
//    normalize(normSJ, max);
////    for (int j = 0; j < normSJ.size(); ++j) {
////        normSJ[j] = 120;
////    }
//
//    shark::RealVector result = rbm.predict(normSJ);
//
//    std::cout << "DBN result new " << std::endl;
//    for (auto it : result) {
//        std::cout << it  << std::endl;
//    }
//
//    shark::RealVector result2 = rbm.predict(norm[1]);
//
//    std::cout << "DBN result trained" << std::endl;
//    for (auto it : result2) {
//        std::cout << it  << std::endl;
//    }
//
//}
//
//TEST_F(RBMTest, DISABLED_testFeauteExractionOther) {
//
//    WaveFile waves[] = {
//                         WaveFile("./tests/wave/waveFiles/testMK.wav"),
//                         WaveFile("./tests/wave/waveFiles/testMK.wav"),
//                         WaveFile("./tests/wave/waveFiles/testMK.wav")};
//    Samples samples[3];
//    std::valarray<jsonextend> propArr(3);
//    FeatureExtractor extractor;
//    extractor.init();
//    for (uint16_t i = 0; i < 3; ++i) {
//        samples[i] = Samples(waves[i]);
//        propArr[i] = extractor.getSummary(samples[i]);
//    }
//
//    RBMConfig config;
//    config.numberOfHidden = 3;
//    config.numberOfVisible = propArr[0].as_object().at(MfccProperty::NAME).size() + propArr[0].as_object().size() - 1;
//    config.batchSize = 1;
//
//    RBM<shark::GaussianBinaryRBM, shark::GaussianBinaryPCD> rbm{config};
//    rbm.train(propArr);
//
//    shark::RealVector result = rbm.getHiddenLaverParameters();
//    ASSERT_EQ(3, result.size());
//    ASSERT_NEAR(98.33, result[0], 1);
//    ASSERT_NEAR(98.58, result[1], 1);
//    ASSERT_NEAR(98.72, result[2], 1);
//
//}

