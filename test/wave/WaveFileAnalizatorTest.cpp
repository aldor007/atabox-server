#include "wave/WaveFileAnalizator.h"
#include "wave/NormalizedSamplesList.h"
#include "../test/wave/NormalizedSampleListMock.h"
#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;

class WaveFileAnalizatorTest: public ::testing::Test {

};

TEST_F(WaveFileAnalizatorTest, findsMaximumCorrectly) {
	//given
	NormalizedSampleListMock waveFile;
	ON_CALL(waveFile, getNumberOfSamples()).WillByDefault(Return(4));
	ON_CALL(waveFile, getSample(0)).WillByDefault(Return(0.128));
	ON_CALL(waveFile, getSample(1)).WillByDefault(Return(0.130));
	ON_CALL(waveFile, getSample(2)).WillByDefault(Return(0.16));
	ON_CALL(waveFile, getSample(3)).WillByDefault(Return(0.130));

	//when
	WaveFileAnalizator analizator;
	double amplitude;
	amplitude = analizator.findAmplitude(waveFile);

	//then
	ASSERT_DOUBLE_EQ(amplitude, 0.16);
}

TEST_F(WaveFileAnalizatorTest, countsZeroCrossingsCorrectly) {
	//given
	NormalizedSampleListMock waveFile;
	ON_CALL(waveFile, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(waveFile, getSample(0)).WillByDefault(Return(-0.12));
	ON_CALL(waveFile, getSample(1)).WillByDefault(Return(-0.130));
	ON_CALL(waveFile, getSample(2)).WillByDefault(Return(0.148));
	ON_CALL(waveFile, getSample(3)).WillByDefault(Return(0.130));
	ON_CALL(waveFile, getSample(4)).WillByDefault(Return(-0.1));

	//when
	WaveFileAnalizator analizator;
	int zeroCrossings = analizator.countZeroCrossings(waveFile);

	//then
	ASSERT_EQ(zeroCrossings, 2);
}

TEST_F(WaveFileAnalizatorTest, countsPercentageAboveCorrectly) {
	//given
	NormalizedSampleListMock waveFile;
	ON_CALL(waveFile, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(waveFile, getSample(0)).WillByDefault(Return(-0.11));
	ON_CALL(waveFile, getSample(1)).WillByDefault(Return(0.7));
	ON_CALL(waveFile, getSample(2)).WillByDefault(Return(0.2));
	ON_CALL(waveFile, getSample(3)).WillByDefault(Return(1));
	ON_CALL(waveFile, getSample(4)).WillByDefault(Return(-1));

	//when
	WaveFileAnalizator analizator;
	double percentageAbove = analizator.percentageAbove(waveFile, 0.5);

	//then
	ASSERT_DOUBLE_EQ(percentageAbove, 3.0/5.0);
}

TEST_F(WaveFileAnalizatorTest, countsPercentageBelowCorrectly) {
	//given
	NormalizedSampleListMock waveFile;
	ON_CALL(waveFile, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(waveFile, getSample(0)).WillByDefault(Return(-0.11));
	ON_CALL(waveFile, getSample(1)).WillByDefault(Return(0.7));
	ON_CALL(waveFile, getSample(2)).WillByDefault(Return(0.2));
	ON_CALL(waveFile, getSample(3)).WillByDefault(Return(1));
	ON_CALL(waveFile, getSample(4)).WillByDefault(Return(-1));

	//when
	WaveFileAnalizator analizator;
	double percentageBelow = analizator.percetnageBelow(waveFile, 0.5);

	//then
	ASSERT_DOUBLE_EQ(percentageBelow, 2.0/5.0);
}


TEST_F(WaveFileAnalizatorTest, realFileHasPositiveNumberOfZeroCrossings) {
	//given
	WaveFile waveFile("test/wave/dziekuje32bit.wav");
	NormalizedSamplesList samples(waveFile);
	WaveFileAnalizator analizator;
	//when
	int crossings = analizator.countZeroCrossings(samples);
	//then
	ASSERT_GT(crossings, 0);
}



