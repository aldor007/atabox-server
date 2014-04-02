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
	const int sizeOfTestData = 2;


	WaveFileMock waveFile;
	ON_CALL(waveFile, getNumberOfSamples()).WillByDefault(
			Return(sizeOfTestData));
	char* values = new char[sizeOfTestData];
	char rawData[] = { 128, 130 };
	memcpy(values, rawData, sizeOfTestData);
	waveFile.setData(values);
	waveFile.setBytePerSample(1);
	//when
	WaveFileAnalizator analizator;
	int amplitude = analizator.findAmplitude(waveFile);
	//then
	ASSERT_EQ(amplitude, 2);
}




