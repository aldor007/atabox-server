/*
 * WavePreprocessor.h
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#ifndef WAVEPREPROCESSOR_H_
#define WAVEPREPROCESSOR_H_
#include "WaveFile.h"
#include "WaveFileAnalizator.h"

class WavePreprocessor {
public:
	WavePreprocessor();
	~WavePreprocessor();
	void deleteSielienceFromBeginningAndEnd(NormalizedSamplesList& sampleList);
	void normalize(WaveFile waveFile);
};

#endif /* WAVEPREPROCESSOR_H_ */
