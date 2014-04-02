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
	fread(&subchunk2Id, 1, 4, file);
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

void WaveFile::freeDataIfNotNull() {
	if (data != NULL) {
		delete data;
		data = NULL;
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

int WaveFile::get8BitSample(int i) {
	int result = ((unsigned char) data[i * bytePerSample]);
	result -= 128;
	return result;
}

int WaveFile::getHighBitSample(int i) {
	return data[i * bytePerSample];
}

int WaveFile::getSample(int i) {
	if (bytePerSample == 1) {
		return get8BitSample(i);
	} else {
		return getHighBitSample(i);
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

