/*
 * WavePreprocessor.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "WavePreprocessor.h"
#include "../analysis/SamplesAnalizator.h"

WavePreprocessor::WavePreprocessor() {

}

WavePreprocessor::~WavePreprocessor() {
}

void WavePreprocessor::deleteSielienceFromBeginningAndEnd(Samples & sampleList, double percentSilence) {
	SamplesAnalizator analizator;
	double amplitude = analizator.findAmplitude(sampleList);
	uint32_t sampleCounter = 0;
		for (uint32_t i = 0; i < sampleList.getNumberOfSamples(); ++i) {
			double sample = sampleList.getSample(i);
			if (fabs(sample) > amplitude*percentSilence) {
				++sampleCounter;
			}
		}

	cx * dataFixed = new cx [sampleCounter + 1];

	sampleCounter = 0;
	for (uint32_t i = 0; i < sampleList.getNumberOfSamples(); ++i) {
			double sample = sampleList.getSample(i);
			if (fabs(sample) > amplitude*percentSilence) {
				dataFixed[++sampleCounter] = sampleList.getSample(i);
			}
		}
	sampleList.setSampleListData(sampleCounter+1,dataFixed);
}

void WavePreprocessor::normalize(WaveFile waveFile) const{

}
