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
	int maxOfRange(WaveFile &waveFile);
	//double percentageAbove(double percentOfMax);
	//double percetnageBelow(double percentOfMax);


};

#endif /* WAVEFILEANALIZATOR_H_ */
