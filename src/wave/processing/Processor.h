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

class Processor {
public:
	Processor();
	virtual ~Processor();
	std::vector<Filter*> filters;
	/*virtual*/
	void addToFilterChain(Filter & filter);
	//virtual
	void addToFilterChain(Filter * filter);
    virtual void applyFilterChainOn(Samples & samples);
	// TODO (optional) Sample applyFilterChain(Samples & samples);


};

#endif /* WAVEPREPROCESSOR_H_ */
