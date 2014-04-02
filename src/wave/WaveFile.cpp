/*
 * WaveFile.cpp
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */

#include "WaveFile.h"

using namespace std;


WaveFile::WaveFile(char * filename) {
	file = fopen(filename, "r");
	if(file==NULL){
		bad_alloc exception;
		throw exception;
	}

}

WaveFile::~WaveFile() {
	fclose(file);
}

