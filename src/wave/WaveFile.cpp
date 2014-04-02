/*
 * WaveFile.cpp
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */

#include "WaveFile.h"

using namespace std;


WaveFile::WaveFile(char * filename) {
	FILE * file = fopen(filename, "r");
	if(file==NULL){
		bad_alloc exception;
		throw exception;
	}
	fread(chunkID, 1, 4, file);
	fread(&chunkSize, 1, 4, file);
	fread(format, 1, 4, file);
	fread(&subchunk1Id, 1, 4, file);
	fread(&subchunk1Size, 1, 4, file);
	fread(&audioFormat, 1, 2, file);
	fread(&numberOfChanels, 1, 2, file);
	fread(&sampleRate, 1, 4, file);
	fread(&byteRate, 1, 4, file);
	fread(&blockAlign, 1, 2, file);
	fread(&bitsPerSample, 1, 2, file);

	fclose(file);
}

WaveFile::~WaveFile() {

}

char * WaveFile::getChunkID(){
	return chunkID;
}
unsigned int WaveFile::getChunkSize(){
	return chunkSize;
}
char * WaveFile::getFormat(){
	return format;
}
char * WaveFile::getSubchunk1Id(){
	return subchunk1Id;
}

unsigned int WaveFile::getSubchunk1Size(){
	return subchunk1Size;
}
unsigned int WaveFile::getAudioFormat(){
	return audioFormat;
}
unsigned int WaveFile::getNumberOfChanels(){
	return numberOfChanels;
}
unsigned int WaveFile::getSampleRate(){
	return sampleRate;
}
unsigned int WaveFile::getByteRate(){
	return byteRate;
}
unsigned int WaveFile::getBlockAlign(){
	return blockAlign;
}
unsigned int WaveFile::getBitsPerSample(){
	return bitsPerSample;
}


