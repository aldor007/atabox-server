
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


/*
 * ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(4));
 * ON_CALL(samples, toArray()).WillByDefault(Return(&samplesArr[0]));
 */

    samples.setSamplesData(&samplesArr[0], 4, 4);

    //when
    MfccProperty property;
    jsonextend mfcc = property.getJSON(samples);
    //then
    ASSERT_DOUBLE_EQ(mfcc[property.getName()][0].as_double(), 0);
}

TEST_F(MfccPropertyTest, returnsCorrectName) {
    //given
    MfccProperty property;

    //when
    string name = property.getName();

    //then
    ASSERT_STRCASEEQ("mfcc", name.c_str());
}

