#include "wave/WaveFileAnalizator.h"
#include "wave/WaveFile.h"
#include "../test/wave/WaveFileMock.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "wave/WavePreprocessor.h"

using ::testing::Return;

class WavePreprocessorTest: public ::testing::Test {

};

TEST_F(WavePreprocessorTest, deleteSielienceFromBeginningAndEnd) {
	//given
	WaveFileMock waveFile;
	ON_CALL(waveFile, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(waveFile, getSample(0)).WillByDefault(Return(1));
	ON_CALL(waveFile, getSample(1)).WillByDefault(Return(128));
	ON_CALL(waveFile, getSample(2)).WillByDefault(Return(130));
	ON_CALL(waveFile, getSample(3)).WillByDefault(Return(148));
	ON_CALL(waveFile, getSample(4)).WillByDefault(Return(130));

	//when
	WavePreprocessor preprocesor;
	preprocesor.deleteSielienceFromBeginningAndEnd(waveFile);

	unsigned int numberOfSamples = waveFile.getNumberOfSamples();
	//then
	ASSERT_EQ(numberOfSamples, 4);
}


