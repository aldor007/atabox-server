#include "wave/WaveFileAnalizator.h"
#include "wave/WaveFile.h"
#include "../test/wave/WaveFileMock.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;

class WaveFileAnalizatorTest: public ::testing::Test {

};

TEST_F(WaveFileAnalizatorTest, findsMaximumCorrectyly) {
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

TEST_F(WaveFileAnalizatorTest, countsZeroCrossingsCorrectyly) {
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
TEST_F(WaveFileAnalizatorTest, countsMaxOfRangeCorrectly) {
	//given
	WaveFileMock waveFile8bit;
	WaveFileMock waveFile32bit;
	ON_CALL(waveFile8bit, getBitsPerSample()).WillByDefault(Return(8));
	ON_CALL(waveFile32bit, getBitsPerSample()).WillByDefault(Return(32));

	//when
	WaveFileAnalizator analizator;
	int maxOfRange8 = analizator.maxOfRange(waveFile8bit);
	int maxOfRange32 = analizator.maxOfRange(waveFile32bit);
	//then
	ASSERT_EQ(maxOfRange8, 127);
	ASSERT_EQ(maxOfRange32, 2147483647);
}

