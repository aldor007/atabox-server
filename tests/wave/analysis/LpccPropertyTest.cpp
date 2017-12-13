#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SamplesMock.h"
#include "wave/analysis/LpccProperty.h"
#include "wave/WaveFile.h"

using ::testing::Return;

class LpccPropertyTest: public ::testing::Test {

};

TEST_F(LpccPropertyTest, calculateCorrect) {
    WaveFile wave("./tests/wave/waveFiles/dziendobryMarcin12.wav");

    Samples sample{wave};

    //when
    LpccProperty property;
    auto data = property.getRealVector(sample);

    for (auto d: data) {
        ASSERT_FALSE( d != d);
        // std::cout << "d = " << d << "\n";
    }
}

TEST_F(LpccPropertyTest, calculateCorrect2) {
    WaveFile wave("./tests/wave/waveFiles/dzienDobryTata1.wav");
    Samples sample{wave};

    //when
    LpccProperty property;
    auto data = property.getRealVector(sample);

    for (auto d: data) {
        ASSERT_FALSE( d != d);
        // std::cout << "d2 = " << d << "\n";
    }
}

TEST_F(LpccPropertyTest, calculateCorrect3) {
    Samples sample(WaveFile("./tests/wave/waveFiles/dziendobryTomek-13.wav"));

    //when
    LpccProperty property;
    auto data = property.getRealVector(sample);

    for (auto d: data) {
        ASSERT_FALSE( d != d);
        ASSERT_TRUE (d != 0);
        // std::cout << "d2 = " << d << "\n";
    }
}
