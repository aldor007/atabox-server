/*
 * WaveFile.cpp
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */

#include "WaveFile.h"

using namespace std;

void WaveFile::readRIFFChunkDescriptor(FILE* file) {
	fread(chunkID, 1, 4, file);
	fread(&chunkSize, 1, 4, file);
	fread(format, 1, 4, file);
}

void WaveFile::readFmtSubchunk(FILE* file) {
	fread(&subchunk1Id, 1, 4, file);
	fread(&subchunk1Size, 1, 4, file);
	fread(&audioFormat, 1, 2, file);
	fread(&numberOfChanels, 1, 2, file);
	fread(&sampleRate, 1, 4, file);
	fread(&byteRate, 1, 4, file);
	fread(&blockAlign, 1, 2, file);
	fread(&bitsPerSample, 1, 2, file);
	bytePerSample = bitsPerSample / 8;
}

void WaveFile::ReadDataSubchunk(FILE* file) {
	skipExtraParams(file);
	fread(&subchunk2Size, 1, 4, file);
	freeDataIfNotNull();
	data = new char[subchunk2Size];
	numberOfSamples = subchunk2Size / (bytePerSample * numberOfChanels);
	fread(data, 1, subchunk2Size, file);
}
WaveFile::WaveFile() {
}

void WaveFile::loadFromFile(char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		bad_alloc exception;
		throw exception;
	}
	readRIFFChunkDescriptor(file);
	validateRIFFChunkDescriptor();
	readFmtSubchunk(file);
	validateFmtSubchunk();
	ReadDataSubchunk(file);
	validateDataSubchunk();
	fclose(file);
	normalizeData();
}

WaveFile::WaveFile(char * filename) {
	loadFromFile(filename);
}

void WaveFile::freeDataIfNotNull() {
	if (data != nullptr) {
		delete data;
		data = nullptr;
	}
}

WaveFile::~WaveFile() {
	freeDataIfNotNull();
}

char * WaveFile::getChunkID() {
	return chunkID;
}
unsigned int WaveFile::getChunkSize() {
	return chunkSize;
}
char * WaveFile::getFormat() {
	return format;
}
char * WaveFile::getSubchunk1Id() {
	return subchunk1Id;
}

unsigned int WaveFile::getSubchunk1Size() {
	return subchunk1Size;
}
unsigned int WaveFile::getAudioFormat() {
	return audioFormat;
}
unsigned int WaveFile::getNumberOfChanels() {
	return numberOfChanels;
}
unsigned int WaveFile::getSampleRate() {
	return sampleRate;
}
unsigned int WaveFile::getByteRate() {
	return byteRate;
}
unsigned int WaveFile::getBlockAlign() {
	return blockAlign;
}
unsigned int WaveFile::getBitsPerSample() {
	return bitsPerSample;
}

unsigned int WaveFile::getSubchunk2Size() {
	return subchunk2Size;
}

char * WaveFile::getSubchunk2Id() {
	return subchunk2Id;
}

int8_t WaveFile::get8BitRawSample(int i) {
	int8_t result = ((unsigned char) data[i * bytePerSample]);
	result -= 128;
	return result;
}

int32_t WaveFile::getHighBitRawSample(int i) {
	int32_t result = 0;
	memcpy(&result, data+(i * bytePerSample), bytePerSample);

	return result;
}

int32_t WaveFile::getRawSample(unsigned int i) {
	if (bytePerSample == 1) {
		return get8BitRawSample(i);
	} else {
		return getHighBitRawSample(i);
	}
}
double WaveFile::getSample(unsigned int i) {
	return this->normalizedData[i];
}


/**
 * Returns max amplitude. This function is used because with different bit-per-sample factor it has different maximum values.
 * For example if we use 8-bits sample value 255 is maximum. When we use 32-bit sample value 255 is relatively small.
 * @param waveFile input file
 * @return maximum value
 */
uint32_t WaveFile::getMaxOfRange() {
	return this->maxOfRange;
}

/**
 * Returns max amplitude. This function is used because with different bit-per-sample factor it has different maximum values.
 * For example if we use 8-bits sample value 255 is maximum. When we use 32-bit sample value 255 is relatively small.
 * @param waveFile input file
 * @return maximum value
 */
void WaveFile::normalizeData() {
	try {
		this->normalizedData = new double[this->numberOfSamples];
	}
	catch(std::bad_alloc) {
		throw "No memmory";
	}
	this->maxOfRange = (1 << (this->bitsPerSample - 1)) - 1;
	for(uint32_t i = 0; i < this->numberOfSamples; i++) {
		this->normalizedData[i] = (double)this->getRawSample(i)/this->maxOfRange;

	}
	if (data != nullptr) {
		delete data;
		data = nullptr;
	}

}
unsigned int WaveFile::getNumberOfSamples() {
	return numberOfSamples;
}

void WaveFile::validateDataSubchunk() {

}

void WaveFile::validateFmtSubchunk() {
	if (numberOfChanels != 1) {
		throw "Only mono files are supported";
	}
}
void WaveFile::validateRIFFChunkDescriptor() {
	if (strncmp(chunkID, "RIFF", 4) != 0) {
		throw "This is not WAVE file.";
	}
}

void WaveFile::skipExtraParams(FILE* file) {
	fread(&subchunk2Id, 1, 4, file);
	while (strncmp(subchunk2Id, "data", 4) != 0){
		fseek(file, -3, SEEK_CUR);
		fread(&subchunk2Id, 1, 4, file);
	}
}
double WaveFile::operator[](unsigned int i) {
	return this->getSample(i);
}
