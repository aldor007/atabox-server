/*
 * WavePreprocessor.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "Preprocessor.h"
#include "../analysis/SamplesAnalizator.h"

Preprocessor::Preprocessor() {

}

Preprocessor::~Preprocessor() {
}

void Preprocessor::addToFilterChain(Filter& filter) {
	filters.push_back(filter);
}

void Preprocessor::applyFilterChainOn(Samples& samples) {
	for (int i = 0; i < filters.size(); ++i) {
		filters[i].applyOn(samples);
	}
}
// TODO move to Filter subclasses
void Preprocessor::deleteSielienceFromBeginningAndEnd(Samples & sampleList, double percentSilence) {
	SamplesAnalizator analizator;
	double amplitude = analizator.findAmplitude(sampleList);
	uint32_t sampleCounter = 0;
		for (uint32_t i = 0; i < sampleList.getNumberOfSamples(); ++i) {
			double sample = sampleList.getSample(i);
			if (fabs(sample) > amplitude*percentSilence) {
				++sampleCounter;
			}
		}

	double * dataFixed = new double [sampleCounter + 1];

	sampleCounter = 0;
	for (uint32_t i = 0; i < sampleList.getNumberOfSamples(); ++i) {
			double sample = sampleList.getSample(i);
			if (fabs(sample) > amplitude*percentSilence) {
				dataFixed[++sampleCounter] = sampleList.getSample(i);
			}
		}
	sampleList.setSampleListData(sampleCounter+1,dataFixed);
}

void Preprocessor::normalize(WaveFile waveFile) const{

}
