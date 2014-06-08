/*
 * ProcessorTest.cpp
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#include <wave/Samples.h>
#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "wave/processing/Processor.h"
#include "../SamplesMock.h"
#include "ConstantAddingTestFilter.h"



using ::testing::Return;

class ProcessorTest: public ::testing::Test {

};

TEST_F(ProcessorTest, doesNotChangesSamplesBeforeFilterAdd) {

	//given
	SamplesMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(4));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(0.128));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(-0.5));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.16));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(0.130));
	Processor preprocessor;

	//when
	preprocessor.applyFilterChainOn(samples);

	//then
	ASSERT_DOUBLE_EQ(samples.getSample(0), 0.128);
	ASSERT_DOUBLE_EQ(samples.getSample(1), -0.5);
	ASSERT_DOUBLE_EQ(samples.getSample(2), 0.16);
	ASSERT_DOUBLE_EQ(samples.getSample(3), 0.130);
}

TEST_F(ProcessorTest, changesSamplesWhenFiltersAreAdded) {

	//given
	Samples samples;
	cx * values = new cx[4];
	values[0] = 0.128;
	values[1] = -0.5;
	values[2] = 0.16;
	values[3] =  0.130;
	samples.setSampleListData(4, values);
	ConstantAddingTestFilter filter(0.5);
	Processor preprocessor;
	preprocessor.addToFilterChain(filter);

	//when
	preprocessor.applyFilterChainOn(samples);

	//then
	ASSERT_DOUBLE_EQ(samples.getSample(0), 0.628);
	ASSERT_DOUBLE_EQ(samples.getSample(1), 0.0);
	ASSERT_DOUBLE_EQ(samples.getSample(2), 0.66);
	ASSERT_DOUBLE_EQ(samples.getSample(3), 0.630);
}

TEST_F(ProcessorTest, changesSamplesWhenMoreThanOneFiltersAreAdded) {

	//given
	Samples samples;
	cx * values = new cx[4];
	values[0] = 0.128;
	values[1] = -0.5;
	values[2] = 0.16;
	values[3] =  0.130;
	samples.setSampleListData(4, values);
	ConstantAddingTestFilter filter(0.2);
	ConstantAddingTestFilter filter2(0.3);
	Processor preprocessor;
	preprocessor.addToFilterChain(filter);
	preprocessor.addToFilterChain(filter2);

	//when
	preprocessor.applyFilterChainOn(samples);

	//then
	ASSERT_DOUBLE_EQ(samples.getSample(0), 0.628);
	ASSERT_DOUBLE_EQ(samples.getSample(1), 0.0);
	ASSERT_DOUBLE_EQ(samples.getSample(2), 0.66);
	ASSERT_DOUBLE_EQ(samples.getSample(3), 0.630);
}

