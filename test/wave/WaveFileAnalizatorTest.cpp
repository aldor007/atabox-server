#include "wave/analysis/SamplesAnalizator.h"
#include "wave/Samples.h"
#include "../test/wave/NormalizedSampleListMock.h"
#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;

class SamplesAnalizatorTest: public ::testing::Test {

};

TEST_F(SamplesAnalizatorTest, findsMaximumCorrectly) {
	//given
	NormalizedSampleListMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(4));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(0.128));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(-0.5));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.16));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(0.130));

	//when
	SamplesAnalizator analizator;
	double amplitude = analizator.findAmplitude(samples);

	//then
	ASSERT_DOUBLE_EQ(amplitude, 0.5);
}

TEST_F(SamplesAnalizatorTest, countsZeroCrossingsCorrectly) {
	//given
	NormalizedSampleListMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(-0.12));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(-0.130));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.148));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(0.130));
	ON_CALL(samples, getSample(4)).WillByDefault(Return(-0.1));

	//when
	SamplesAnalizator analizator;
	int zeroCrossings = analizator.countZeroCrossings(samples);

	//then
	ASSERT_EQ(zeroCrossings, 2);
}

TEST_F(SamplesAnalizatorTest, countsPercentageAboveCorrectly) {
	//given
	NormalizedSampleListMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(-0.11));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(0.7));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.2));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(1));
	ON_CALL(samples, getSample(4)).WillByDefault(Return(-1));

	//when
	SamplesAnalizator analizator;
	double percentageAbove = analizator.percentageAbove(samples, 0.5);

	//then
	ASSERT_DOUBLE_EQ(percentageAbove, 3.0/5.0);
}

TEST_F(SamplesAnalizatorTest, countsPercentageBelowCorrectly) {
	//given
	NormalizedSampleListMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(-0.11));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(0.7));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.2));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(1));
	ON_CALL(samples, getSample(4)).WillByDefault(Return(-1));

	//when
	SamplesAnalizator analizator;
	double percentageBelow = analizator.percetnageBelow(samples, 0.5);

	//then
	ASSERT_DOUBLE_EQ(percentageBelow, 2.0/5.0);
}


TEST_F(SamplesAnalizatorTest, realFileHasPositiveNumberOfZeroCrossings) {
	//given
	WaveFile waveFile("test/wave/waveFiles/dziekuje32bit.wav");
	Samples samples(waveFile);
	SamplesAnalizator analizator;
	//when
	int crossings = analizator.countZeroCrossings(samples);
	//then
	ASSERT_GT(crossings, 0);
}



