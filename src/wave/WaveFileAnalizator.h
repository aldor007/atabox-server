/*
 * WaveFileAnalizator.h
 *
 *  Created on: Apr 2, 2014
 *      Author: mj
 */

#ifndef WAVEFILEANALIZATOR_H_
#define WAVEFILEANALIZATOR_H_
#include "WaveFile.h"

class WaveFileAnalizator {
public:
	WaveFileAnalizator();
	virtual ~WaveFileAnalizator();
	int findAmplitude(WaveFile &waveFile);
	int countZeroCrossings(WaveFile &waveFile);

};

#endif /* WAVEFILEANALIZATOR_H_ */
