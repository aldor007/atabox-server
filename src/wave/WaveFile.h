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
#include <vector>
/**
 * Class describes wave file. It supports only mono files.
 */
class WaveFile {
public:

	WaveFile(char * filename);
	WaveFile(std::vector<uint8_t> &data);
	virtual ~WaveFile();
	virtual char * getChunkID();
	virtual unsigned int getChunkSize();
	virtual char * getFormat();
	virtual char * getSubchunk1Id();
	virtual unsigned int getSubchunk1Size();
	virtual unsigned int getAudioFormat();
	virtual unsigned int getNumberOfChanels();
	virtual unsigned int getSampleRate();
	virtual unsigned int getByteRate();
	virtual unsigned int getBlockAlign();
	virtual unsigned int getBitsPerSample();
	virtual char * getSubchunk2Id();
	virtual unsigned int getSubchunk2Size();
	virtual double getSample(unsigned int i);
	virtual unsigned int getNumberOfSamples();
	void loadFromFile(char* filename);
	void loadFromVector(std::vector<uint8_t> &data);
	virtual double	 operator[](unsigned int i);
	virtual uint32_t getMaxOfRange();
protected:
	WaveFile();
	//chunk descriptor
	virtual int32_t getRawSample(unsigned int i);
	virtual inline int8_t get8BitRawSample(int i);
	virtual inline int32_t getHighBitRawSample(int i);
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

	char * data = nullptr;
	double * normalizedData = nullptr;

	uint32_t maxOfRange = 0;

	void readRIFFChunkDescriptor(FILE* file);
	void readFmtSubchunk(FILE* file);
	void ReadDataSubchunk(FILE* file);
	void normalizeData();


	void validateRIFFChunkDescriptor();
	void validateFmtSubchunk();
	void validateDataSubchunk();
	void freeDataIfNotNull();
	void skipExtraParams(FILE* file);
};

#endif /* WAVEFILE_H_ */
