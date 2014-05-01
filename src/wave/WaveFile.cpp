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
}

WaveFile::WaveFile(char * filename) {
	loadFromFile(filename);
}
WaveFile::WaveFile(std::vector<uint8_t> &data) {
	loadFromVector(data);
}

void WaveFile::loadFromVector(std::vector<uint8_t> &data) {
//TODO:
	//uint32_t currenIndex = 0;
	//data.data()

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

int32_t WaveFile::getRawSample(unsigned int i) {
	int32_t result = 0;
	memcpy(&result, data + (i * bytePerSample), bytePerSample);
	return result;
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
	while (strncmp(subchunk2Id, "data", 4) != 0) {
		fseek(file, -3, SEEK_CUR);
		fread(&subchunk2Id, 1, 4, file);
	}
}
double WaveFile::operator[](unsigned int i) {
	return data[i];
}
void WaveFile::setSampleData(uint32_t numberOfSamples,double * data) {
	if (this->normalizedData != nullptr) {
			delete this->normalizedData;
		}
	this->normalizedData = data;
	this->numberOfSamples = numberOfSamples;
}
