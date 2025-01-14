/*
 * SilenceCuttingFilterTest.cpp
 *
 *  Created on: 6 cze 2014
 *      Author: mj
 */

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
#include <wave/processing/preprocessing/SilenceCuttingFilter.h>

using ::testing::Return;

class SilenceCuttingFilterTest: public ::testing::Test {

};

TEST_F(SilenceCuttingFilterTest, trivialExampleForBeginning) {

	//given
	Samples samples;
	double * values = new double[2];
	values[0] = 0.0128;
	values[1] = -0.5;

	samples.setSamplesData(values, 2, 2);
	//delete[] values;
	SilenceCuttingFilter filter(0.1);
	Processor preprocessor;
	preprocessor.addToFilterChain(filter);

	//when
	preprocessor.applyFilterChainOn(samples);

	delete[] values;
	//then
	ASSERT_DOUBLE_EQ(samples.getSample(0), -0.5);

}

TEST_F(SilenceCuttingFilterTest, chanchesLenghtCorrectly) {

	//given
	Samples samples;
	double * values = new double[2];
	values[0] = 0.0128;
	values[1] = -0.5;

	samples.setSamplesData(values, 2, 1);
	double oldLength = samples.getLenghtInSeconds();

	SilenceCuttingFilter filter(0.1);
	Processor preprocessor;
	preprocessor.addToFilterChain(filter);

	//when
	preprocessor.applyFilterChainOn(samples);

	delete[] values;
	//then
	ASSERT_GT(oldLength, 0);
	ASSERT_DOUBLE_EQ(oldLength / 2, samples.getLenghtInSeconds());

}

TEST_F(SilenceCuttingFilterTest, filterRemovesSilenceFromBeginningAndEnd) {

	//given
	Samples samples;
	double * values = new double[8];
	values[0] = 0.0128;
	values[1] = -0.05;
	values[2] = 0.16;
	values[3] = 0.130;
	values[4] = 0.128;
	values[5] = -0.5;
	values[6] = 0.016;
	values[7] = 0.013;
	samples.setSamplesData(values, 8, 8);
	SilenceCuttingFilter filter(0.1);
	Processor preprocessor;
	preprocessor.addToFilterChain(filter);

	//when
	preprocessor.applyFilterChainOn(samples);

	delete[] values;
	//then
	ASSERT_EQ(samples.getNumberOfSamples(), 4);
	ASSERT_DOUBLE_EQ(samples.getSample(0), 0.16);
	ASSERT_DOUBLE_EQ(samples.getSample(1), 0.130);
	ASSERT_DOUBLE_EQ(samples.getSample(2), 0.128);
	ASSERT_DOUBLE_EQ(samples.getSample(3), -0.5);
}

TEST_F(SilenceCuttingFilterTest, filterRemovesSilenceFromEnd) {

	//given
	Samples samples;
	double * values = new double[4];
	values[0] = 0.128;
	values[1] = -0.5;
	values[2] = 0.016;
	values[3] = 0.0130;
	samples.setSamplesData(values, 4, 4);
	SilenceCuttingFilter filter(0.1);
	Processor preprocessor;
	preprocessor.addToFilterChain(filter);

	//when
	preprocessor.applyFilterChainOn(samples);

	delete[] values;
	//then
	ASSERT_EQ(samples.getNumberOfSamples(), 2);
	ASSERT_DOUBLE_EQ(samples.getSample(0), 0.128);
	ASSERT_DOUBLE_EQ(samples.getSample(1), -0.5);
}

TEST_F(SilenceCuttingFilterTest, doesNotRemovesAnythingWhenThereIsNoSilence) {

	//given
	Samples samples;
	double * values = new double[4];
	values[0] = 0.128;
	values[1] = -0.5;
	values[2] = 0.16;
	values[3] = 0.130;
	samples.setSamplesData(values, 4, 4);
	SilenceCuttingFilter filter(0.1);
	Processor preprocessor;
	preprocessor.addToFilterChain(filter);

	//when
	preprocessor.applyFilterChainOn(samples);

	delete[] values;
	//then
	ASSERT_EQ(samples.getNumberOfSamples(), 4);
	ASSERT_DOUBLE_EQ(samples.getSample(0), 0.128);
	ASSERT_DOUBLE_EQ(samples.getSample(1), -0.5);
	ASSERT_DOUBLE_EQ(samples.getSample(2), 0.16);
	ASSERT_DOUBLE_EQ(samples.getSample(3), 0.130);
}

TEST_F(SilenceCuttingFilterTest, doesNotRemovesSilenceFromMiddle) {

	//given
	Samples samples;
	double * values = new double[4];
	values[0] = 0.128;
	values[1] =	0;
	values[2] = 0.16;
	values[3] = 0.130;
	samples.setSamplesData(values, 4, 4);
	SilenceCuttingFilter filter(0.1);
	Processor preprocessor;
	preprocessor.addToFilterChain(filter);

	//when
	preprocessor.applyFilterChainOn(samples);

	delete[] values;
	//then
	ASSERT_EQ(samples.getNumberOfSamples(), 4);
	ASSERT_DOUBLE_EQ(samples.getSample(0), 0.128);
	ASSERT_DOUBLE_EQ(samples.getSample(1), 0);
	ASSERT_DOUBLE_EQ(samples.getSample(2), 0.16);
	ASSERT_DOUBLE_EQ(samples.getSample(3), 0.130);
}

TEST_F(SilenceCuttingFilterTest, testRemoveSilence) {
	WaveFile wave{"./tests/wave/waveFiles/prosze32bit.wav"};

	Samples sample{wave};
	sample.draw("./tests/silen-befor.png");
	SilenceCuttingFilter filter(0.05);
	Processor preprocessor;
	preprocessor.addToFilterChain(filter);

	//when
	preprocessor.applyFilterChainOn(sample);
	sample.draw("./tests/silen-after.png");
}

