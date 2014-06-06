/*
 * waveWavePreprocessorTest.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "wave/preprocessing/WavePreprocessor.h"
#include "wave/analysis/SamplesAnalizator.h"
#undef U
#include "gtest/gtest.h"

class WavePreprocessorTest: public ::testing::Test {

};

TEST_F(WavePreprocessorTest, deleteSielienceFromBeginningAndEnd) {

	WaveFile wave1("test/wave/waveFiles/dziekuje32bit.wav");
	WaveFile waveSilence("test/wave/waveFiles/dziekuje32bit300msecSilence.wav");
	Samples samples1(wave1);
	Samples samplesSilence(waveSilence);
	ASSERT_NE(samples1[300], samplesSilence[300]);
	ASSERT_TRUE(samples1[232] != samplesSilence[232]);
	ASSERT_NE(samples1.getNumberOfSamples() , samplesSilence.getNumberOfSamples());
	WavePreprocessor processor;
	processor.deleteSielienceFromBeginningAndEnd(samplesSilence, 0.05);
	//ASSERT_DOUBLE_EQ(samples1[80], samplesSilence[80]);
	//ASSERT_DOUBLE_EQ(samples1[150], samplesSilence[150]);
	ASSERT_NEAR(samples1.getNumberOfSamples() - wave1.getSampleRate() * 0.3,
			samplesSilence.getNumberOfSamples(), wave1.getSampleRate()/ 4.0);
	ASSERT_NEAR(samples1.getLenghtInSeconds()/2.0, samplesSilence.getLenghtInSeconds(), 0.05);


}
