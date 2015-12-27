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
/**
 * Class describes wave file. It supports only mono files.
 */
class Samples;
class WaveFile {
public:

	WaveFile(const char * filename);
	WaveFile(uint8_t  *data, uint32_t content_lenght);
	virtual ~WaveFile();
	virtual char * getChunkID();
	virtual uint32_t getChunkSize();
	virtual char * getFormat();
	virtual char * getSubchunk1Id();
	virtual uint32_t getSubchunk1Size();
	virtual uint16_t getAudioFormat();
	virtual uint16_t getNumberOfChanels();
	virtual uint32_t getSampleRate();
	virtual uint32_t getByteRate();
	virtual uint16_t getBlockAlign();
	virtual uint16_t getBitsPerSample();
	virtual char * getSubchunk2Id();
	virtual uint32_t getSubchunk2Size();
	virtual uint32_t getNumberOfSamples();
	void loadFromFile(const char* filename);
	void loadFromMemory(uint8_t  * data, uint32_t content_len);
	virtual double	 operator[](unsigned int i);
	virtual int32_t getRawSample(unsigned int i);
	virtual char* getSamples();
	operator Samples () const;
	WaveFile& operator=(WaveFile&& other);
	WaveFile(const WaveFile& other);
protected:
	WaveFile();
	//chunk descriptor
	char chunkID[4] = { 0 };
	uint32_t chunkSize = 0;
	char format[4] = { 0 };
	// subchunk 1
	char subchunk1Id[4] = { 0 };
	uint32_t subchunk1Size = 0;
	uint16_t audioFormat = 0;
	uint16_t numberOfChanels = 0;
	uint32_t sampleRate = 0;
	uint32_t byteRate = 0;
	uint16_t blockAlign = 0;
	uint16_t bitsPerSample = 0;
	uint8_t bytePerSample = 0;
	//subchunk 2
	char subchunk2Id[4] = { 0 };
	uint32_t subchunk2Size = 0;
	uint32_t numberOfSamples = 0;

	char * data = nullptr;


	void readRIFFChunkDescriptor(FILE* file);
	void readFmtSubchunk(FILE* file);
	void ReadDataSubchunk(FILE* file);


	void validateRIFFChunkDescriptor() const;
	void validateFmtSubchunk() const;
	void validateDataSubchunk() const;
	void freeDataIfNotNull();
	void skipExtraParams(FILE* file);
};

#endif /* WAVEFILE_H_ */
