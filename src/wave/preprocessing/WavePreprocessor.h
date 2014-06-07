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
#include "Filter.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;


class WavePreprocessor {
public:
	WavePreprocessor();
	~WavePreprocessor();
	vector<Filter> filters;
	void addToFilterChain(Filter & filter);
	void applyFilterChainOn(Samples & samples);
	// TODO Sample applyFilterChain(Samples & samples);

 //TODO move to Filter subclasses
	static void deleteSielienceFromBeginningAndEnd(Samples& sampleList,
			double percentSilence = 0.02) ;
	void normalize(WaveFile waveFile) const;
};

#endif /* WAVEPREPROCESSOR_H_ */
