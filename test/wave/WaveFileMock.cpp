/*
 * WaveFileMock.cpp
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */

#include "WaveFileMock.h"

WaveFileMock::WaveFileMock() {
	bytePerSample = 1;

}

WaveFileMock::~WaveFileMock() {
	// TODO Auto-generated destructor stub
}

void WaveFileMock::setData(void * data){
	this->data = (char *)data;
}

void WaveFileMock::setBytePerSample(int i){
	this->bytePerSample = i;
}

