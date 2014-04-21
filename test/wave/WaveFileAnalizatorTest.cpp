#include "wave/WaveFileAnalizator.h"
#include "wave/WaveFile.h"
#include "../test/wave/WaveFileMock.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;

class WaveFileAnalizatorTest: public ::testing::Test {

};

TEST_F(WaveFileAnalizatorTest, findsMaximumCorrectly) {
	//given
	WaveFileMock waveFile;
	ON_CALL(waveFile, getNumberOfSamples()).WillByDefault(Return(4));
	ON_CALL(waveFile, getSample(0)).WillByDefault(Return(128));
	ON_CALL(waveFile, getSample(1)).WillByDefault(Return(130));
	ON_CALL(waveFile, getSample(2)).WillByDefault(Return(148));
	ON_CALL(waveFile, getSample(3)).WillByDefault(Return(130));

	//when
	WaveFileAnalizator analizator;
	int amplitude = analizator.findAmplitude(waveFile);

	//then
	ASSERT_EQ(amplitude, 148);
}

TEST_F(WaveFileAnalizatorTest, countsZeroCrossingsCorrectly) {
	//given
	WaveFileMock waveFile;
	ON_CALL(waveFile, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(waveFile, getSample(0)).WillByDefault(Return(-12));
	ON_CALL(waveFile, getSample(1)).WillByDefault(Return(-130));
	ON_CALL(waveFile, getSample(2)).WillByDefault(Return(148));
	ON_CALL(waveFile, getSample(3)).WillByDefault(Return(130));
	ON_CALL(waveFile, getSample(4)).WillByDefault(Return(-1));

	//when
	WaveFileAnalizator analizator;
	int zeroCrossings = analizator.countZeroCrossings(waveFile);

	//then
	ASSERT_EQ(zeroCrossings, 2);
}

TEST_F(WaveFileAnalizatorTest, countsPercentageAboveCorrectly) {
	//given
	WaveFileMock waveFile;
	ON_CALL(waveFile, getBitsPerSample()).WillByDefault(Return(8));
	ON_CALL(waveFile, getMaxOfRange()).WillByDefault(Return(127));
	ON_CALL(waveFile, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(waveFile, getSample(0)).WillByDefault(Return(-12));
	ON_CALL(waveFile, getSample(1)).WillByDefault(Return(-130));
	ON_CALL(waveFile, getSample(2)).WillByDefault(Return(148));
	ON_CALL(waveFile, getSample(3)).WillByDefault(Return(130));
	ON_CALL(waveFile, getSample(4)).WillByDefault(Return(-1));

	//when
	WaveFileAnalizator analizator;
	double percentageAbove = analizator.percentageAbove(waveFile, 0.5);

	//then
	ASSERT_DOUBLE_EQ(percentageAbove, 3.0/5.0);
}

TEST_F(WaveFileAnalizatorTest, countsPercentageBelowCorrectly) {
	//given
	WaveFileMock waveFile;
	ON_CALL(waveFile, getBitsPerSample()).WillByDefault(Return(8));
	ON_CALL(waveFile, getMaxOfRange()).WillByDefault(Return(127));
	ON_CALL(waveFile, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(waveFile, getSample(0)).WillByDefault(Return(-12));
	ON_CALL(waveFile, getSample(1)).WillByDefault(Return(-130));
	ON_CALL(waveFile, getSample(2)).WillByDefault(Return(148));
	ON_CALL(waveFile, getSample(3)).WillByDefault(Return(130));
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
	WaveFileAnalizator analizator;
	//when
	int crossings= analizator.countZeroCrossings(waveFile);
	//then
	ASSERT_GT(crossings, 0);
}



