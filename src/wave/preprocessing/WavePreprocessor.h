/*
 * WavePreprocessor.h
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#ifndef WAVEPREPROCESSOR_H_
#define WAVEPREPROCESSOR_H_
#include "../WaveFile.h"
#include "../analysis/SamplesAnalizator.h"

class WavePreprocessor {
public:
	WavePreprocessor();
	~WavePreprocessor();
	static void deleteSielienceFromBeginningAndEnd(Samples& sampleList,
			double percentSilence = 0.02) ;
	void normalize(WaveFile waveFile) const;
};

#endif /* WAVEPREPROCESSOR_H_ */
