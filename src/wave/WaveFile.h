/*
 * WaveFile.h
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */

#ifndef WAVEFILE_H_
#define WAVEFILE_H_
#include <stdio.h>
#include <iostream>
class WaveFile {
public:
	WaveFile(char * filename);
	~WaveFile();
private:
	FILE * file;
};



#endif /* WAVEFILE_H_ */
