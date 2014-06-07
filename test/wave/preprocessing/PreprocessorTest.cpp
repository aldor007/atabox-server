/*
 * PreprocessorTest.cpp
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#include <wave/Samples.h>
#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "wave/preprocessing/Preprocessor.h"
#include "../SamplesMock.h"


using ::testing::Return;

class PreprocessorTest: public ::testing::Test {

};

TEST_F(PreprocessorTest, doesNotChangesSamplesBeforeFilterAdd) {
	//given
	SamplesMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(4));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(0.128));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(-0.5));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.16));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(0.130));
	Preprocessor preprocessor;
	//when
	preprocessor.applyFilterChainOn(samples);
	//then
	ASSERT_DOUBLE_EQ(samples.getSample(0), 0.128);
	ASSERT_DOUBLE_EQ(samples.getSample(1), -0.5);
	ASSERT_DOUBLE_EQ(samples.getSample(2), 0.16);
	ASSERT_DOUBLE_EQ(samples.getSample(3), 0.130);
}


