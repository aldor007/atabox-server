#include "wave/WaveFileAnalizator.h"
#include "wave/WaveFile.h"
#include "gtest/gtest.h"

class WaveFileAnalizatorTest: public ::testing::Test {

};

TEST_F(WaveFileAnalizatorTest, findsMaximumCorrectyly) {
	WaveFile waveFile("test/wave/8bitSilenceWithTenAtTheEnd.wav");
	WaveFileAnalizator analizator;
	int maximum = analizator.findMaximum(waveFile);
	ASSERT_EQ(maximum, 10);
}
