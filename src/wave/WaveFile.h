/*
 * WaveFile.h
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */

#ifndef WAVEFILE_H_
#define WAVEFILE_H_
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>

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
	char * getSubchunk2Id();
	unsigned int getSubchunk2Size();
	int getSample(int i);
	inline int get8BitSample(int i);
	inline int getHighBitSample(int i);
	unsigned int getNumberOfSamples();
	void * getRawData();
private:
	//chunk descriptor
	char chunkID[4] = { 0 };
	unsigned int chunkSize = 0;
	char format[4] = { 0 };
	// subchunk 1
	char subchunk1Id[4] = { 0 };
	unsigned int subchunk1Size = 0;
	unsigned int audioFormat = 0;
	unsigned int numberOfChanels = 0;
	unsigned int sampleRate = 0;
	unsigned int byteRate = 0;
	unsigned int blockAlign = 0;
	unsigned int bitsPerSample = 0;
	unsigned int bytePerSample = 0;
	//subchunk 2
	char subchunk2Id[4] = { 0 };
	unsigned int subchunk2Size = 0;
	unsigned int numberOfSamples = 0;

	void readRIFFChunkDescriptor(FILE* file);
	void readFmtSubchunk(FILE* file);
	void ReadDataSubchunk(FILE* file);

	char * data;


	void validateRIFFChunkDescriptor();
	void validateFmtSubchunk();
	void validateDataSubchunk();

};

#endif /* WAVEFILE_H_ */
