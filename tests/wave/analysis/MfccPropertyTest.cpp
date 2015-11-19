
/*
 * MfccPropertyTest.cpp
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SamplesMock.h"
#include "wave/analysis/MfccProperty.h"
#include "wave/WaveFile.h"

using ::testing::Return;

class MfccPropertyTest: public ::testing::Test {

};

TEST_F(MfccPropertyTest, calculateCorrect) {
    //given
    Samples samples;
    const double  samplesArr[4] = {0.15, 0.5, 0.5, 0.3};

    samples.setSamplesData(&samplesArr[0], 4, 4);

    //when
    MfccProperty property;
    jsonextend mfcc = property.getJSON(samples);
    //then
    ASSERT_DOUBLE_EQ(mfcc[property.getName()][0].as_double(), 0);
}

TEST_F(MfccPropertyTest, calculateCorrectWhenTwoFrames) {
    //given
    Samples samples;
    const double  samplesArr[4] = {23.15, 234.5, 0.5, 0.3};
    // multiple it because of that frame have to be 20ms
    samples.setSamplesData(&samplesArr[0], 4, 2*500);

    //when
    MfccProperty property;
    jsonextend mfcc = property.getJSON(samples);
    //then
    ASSERT_EQ(mfcc[property.getName()].size(), 24);

}
TEST_F(MfccPropertyTest, returnsCorrectName) {
    //given
    MfccProperty property;

    //when
    std::string name = property.getName();

    //then
    ASSERT_STRCASEEQ("mfcc", name.c_str());
}

