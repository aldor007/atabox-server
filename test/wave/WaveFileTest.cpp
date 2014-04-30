/*
 * WaveFileTest.cpp
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */

#include "wave/WaveFile.h"
#include "gtest/gtest.h"

class WaveFileTest: public ::testing::Test {

};

TEST_F(WaveFileTest, throwsExceptionWhenFileDoesNotExist) {
	ASSERT_THROW(WaveFile("nonExistingFile.wav"), std::bad_alloc);
}

TEST_F(WaveFileTest, doesntThrowExceptionWhenFileExists) {
	ASSERT_NO_THROW(WaveFile("test/wave/bells.wav"));
}

TEST_F(WaveFileTest, readsChunkIDCorrectly) {
	WaveFile waveFile("test/wave/bells.wav");
	char * chunkID = waveFile.getChunkID();
	ASSERT_EQ(strncmp(chunkID, "RIFF", 4), 0);
}

TEST_F(WaveFileTest, readsChunkSizeCorrectly) {
	WaveFile waveFile("test/wave/bells.wav");
	unsigned int chunkSize = waveFile.getChunkSize();
	ASSERT_EQ(chunkSize, 79370);
}

TEST_F(WaveFileTest, readsFormatCorrectly) {
	WaveFile waveFile("test/wave/bells.wav");
	char * format = waveFile.getFormat();
	ASSERT_EQ(strncmp(format, "WAVE", 4), 0);
}

TEST_F(WaveFileTest, readsSubchunk1IdCorrectly) {
	WaveFile waveFile("test/wave/bells.wav");
	char * subchunk1Id = waveFile.getSubchunk1Id();
	ASSERT_EQ(strncmp(subchunk1Id, "fmt ", 4), 0);
}

TEST_F(WaveFileTest, readsSubchunk1SizeCorrectly) {
	WaveFile waveFile("test/wave/bells.wav");
	unsigned int subchunk1Size = waveFile.getSubchunk1Size();
	ASSERT_EQ(subchunk1Size, 16);
}

TEST_F(WaveFileTest, readsAudioFormatCorrectly) {
	WaveFile waveFile("test/wave/bells.wav");
	unsigned int audioFormat = waveFile.getAudioFormat();
	ASSERT_EQ(audioFormat, 1);
}

TEST_F(WaveFileTest, readsNumberOfChanelsCorrectly) {
	WaveFile waveFile("test/wave/bells.wav");
	unsigned int numberOfChanels = waveFile.getNumberOfChanels();
	ASSERT_EQ(numberOfChanels, 1);
}

TEST_F(WaveFileTest, readsSampleRateCorrectly) {
	WaveFile waveFile("test/wave/bells.wav");
	unsigned int sampleRate = waveFile.getSampleRate();
	ASSERT_EQ(sampleRate, 11025);
}
TEST_F(WaveFileTest, readsByteRateCorrectly) {
	WaveFile waveFile("test/wave/bells.wav");
	unsigned int byteRate = waveFile.getByteRate();
	ASSERT_EQ(byteRate, 11025);
}
TEST_F(WaveFileTest, readsBlockAlignCorrectly) {
	WaveFile waveFile("test/wave/bells.wav");
	unsigned int blockAlign = waveFile.getBlockAlign();
	ASSERT_EQ(blockAlign, 1);
}
TEST_F(WaveFileTest, readsBitPerSampleCorrectly) {
	WaveFile waveFile("test/wave/bells.wav");
	unsigned int bitsPerSample = waveFile.getBitsPerSample();
	ASSERT_EQ(bitsPerSample, 8);
}

TEST_F(WaveFileTest, readsSubchunk2IdCorrectly) {
	WaveFile waveFile("test/wave/bells.wav");
	char * subchunk2Id = waveFile.getSubchunk2Id();
	ASSERT_EQ(strncmp(subchunk2Id, "data", 4), 0);
}

TEST_F(WaveFileTest, readsSubchunk2SizeCorrectly) {
	WaveFile waveFile("test/wave/bells.wav");
	unsigned int subchunk2Size = waveFile.getSubchunk2Size();
	ASSERT_EQ(subchunk2Size, 79334);
}

TEST_F(WaveFileTest, readsDataCorrectlyFor8Bits) {
	WaveFile waveFile("test/wave/8bitSilence.wav");
	int firstSample = waveFile.getRawSample(0);
	for (unsigned int i = 0; i < waveFile.getNumberOfSamples(); ++i) {
		int sample = waveFile.getRawSample(i);
		ASSERT_TRUE(sample == 127 || sample == 128);
	}
}

TEST_F(WaveFileTest, readsDataCorrectlyForMoreThan8Bits) {
	WaveFile waveFile("test/wave/32bitSilence.wav");
	for (int i = 0; i < waveFile.getNumberOfSamples(); ++i) {

		ASSERT_EQ(waveFile.getRawSample(i), 0);
	}
}

TEST_F(WaveFileTest, calculateNumberOfSamplesCorrectly) {
	WaveFile waveFile("test/wave/bells.wav");
	unsigned int numberOfSamples = waveFile.getNumberOfSamples();
	ASSERT_EQ(numberOfSamples, 79334);
}

TEST_F(WaveFileTest, lastSampleMachesEndOfFile) {
	WaveFile waveFile("test/wave/8bitSilenceWithTenAtTheEnd.wav");
	int indexOfLastSample = waveFile.getNumberOfSamples() - 1;
	ASSERT_EQ(waveFile.getRawSample(indexOfLastSample), 138);

}
TEST_F(WaveFileTest, canHandleCommentsInHeader) {
	// given
	WaveFile waveFile("test/wave/dziekuje32bit.wav");
	// when
	int sample = waveFile.getRawSample(1);
	// then
	ASSERT_EQ(446880, sample);

}
