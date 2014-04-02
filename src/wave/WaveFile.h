/*
 * WaveFile.h
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */

#ifndef WAVEFILE_H_
#define WAVEFILE_H_
#include <stdio.h>
#include <iostream>
class WaveFile {
public:
	WaveFile(char * filename);
	~WaveFile();
	char * getChunkID();
	unsigned int getChunkSize();
	char * getFormat();
	char * getSubchunk1Id();
	unsigned int getSubchunk1Size();
	unsigned int getAudioFormat();
	unsigned int getNumberOfChanels();
	unsigned int getSampleRate();
	unsigned int getByteRate();
	unsigned int getBlockAlign();
	unsigned int getBitsPerSample();
private:
	char chunkID[4] = { 0 };
	unsigned int chunkSize = 0;
	char format[4] = { 0 };
	char subchunk1Id[4] = { 0 };
	unsigned int subchunk1Size;
	unsigned int audioFormat = 0;
	unsigned int numberOfChanels = 0;
	unsigned int sampleRate = 0;
	unsigned int byteRate = 0;
	unsigned int blockAlign = 0;
	unsigned int bitsPerSample = 0;
};

#endif /* WAVEFILE_H_ */
