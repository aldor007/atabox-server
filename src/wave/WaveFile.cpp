/*
 * WaveFile.cpp
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */

#include "WaveFile.h"
#include <fstream>
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

void WaveFile::loadFromFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		std::bad_alloc exception;
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

WaveFile::WaveFile(const char * filename) {
	loadFromFile(filename);
}

WaveFile::WaveFile(uint8_t * tmpdata) {
	loadFromMemory(tmpdata);

}

void WaveFile::loadFromMemory(uint8_t *tmpData) {


	uint32_t currentIndex = 0;
	std::memcpy(chunkID, tmpData + currentIndex, 4);
	currentIndex += 4;
	std::memcpy(&chunkSize, tmpData + currentIndex, 4);
	currentIndex += 4;
	std::memcpy(format,  tmpData, 4);
	currentIndex += 4;
	std::memcpy(&numberOfChanels, tmpData + 22, 2);
	std::memcpy(&subchunk1Id, tmpData + 12, 4);
	std::memcpy(&subchunk1Size, tmpData + 16, 4);
	std::memcpy(&audioFormat, tmpData + 20, 2);
	std::memcpy(&numberOfChanels, tmpData + 22, 2);
	std::memcpy(&sampleRate, tmpData + 24, 4);
	std::memcpy(&byteRate, tmpData + 28, 4);
	std::memcpy(&blockAlign, tmpData + 32, 2);
	currentIndex = 34;
	std::memcpy(&bitsPerSample, tmpData + currentIndex, 2 );
	currentIndex += 2;
	bytePerSample = bitsPerSample / 8;
	std::memcpy(subchunk2Id, tmpData + currentIndex, 4 );
	currentIndex += 4;
	while (strncmp(subchunk2Id, "data", 4) != 0){
		currentIndex -= 3;
		std::memcpy(subchunk2Id, tmpData + currentIndex, 4);
		currentIndex += 4;
	}
	freeDataIfNotNull();
	std::memcpy(&subchunk2Size, &tmpData[currentIndex], 4);
	currentIndex += 4;
	data = new char[subchunk2Size];
	numberOfSamples = subchunk2Size / (bytePerSample * numberOfChanels);
	std::memcpy(data, tmpData + currentIndex, subchunk2Size);

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

void WaveFile::validateDataSubchunk() const{

}

void WaveFile::validateFmtSubchunk() const{
	if (numberOfChanels != 1) {
		throw "Only mono files are supported";
	}
}
void WaveFile::validateRIFFChunkDescriptor() const{
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
