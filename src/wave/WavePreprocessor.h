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
	void deleteSielienceFromBeginningAndEnd(NormalizedSamplesList& sampleList,
			double percentSilence = 0.02) const;
	void normalize(WaveFile waveFile) const;
};

#endif /* WAVEPREPROCESSOR_H_ */
