#include "wave/WaveFileAnalizator.h"
#include "wave/WaveFile.h"
#include "../test/wave/WaveFileMock.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;

class WaveFileAnalizatorTest: public ::testing::Test {

};

TEST_F(WaveFileAnalizatorTest, findsMaximumFor8BitsCorrectyly) {
	//given
	WaveFileMock waveFile;
	ON_CALL(waveFile, getNumberOfSamples()).WillByDefault(
			Return(4));
	ON_CALL(waveFile, getSample(0)).WillByDefault(
			Return(128));
	ON_CALL(waveFile, getSample(1)).WillByDefault(
			Return(130));
	ON_CALL(waveFile, getSample(2)).WillByDefault(
			Return(148));
	ON_CALL(waveFile, getSample(3)).WillByDefault(
			Return(130));
	//when
	WaveFileAnalizator analizator;
	int amplitude = analizator.findAmplitude(waveFile);
	//then
	ASSERT_EQ(amplitude, 148);
}




