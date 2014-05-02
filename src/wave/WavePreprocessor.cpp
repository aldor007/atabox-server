/*
 * WavePreprocessor.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "WavePreprocessor.h"
#include "WaveFileAnalizator.h"

WavePreprocessor::WavePreprocessor() {

}

WavePreprocessor::~WavePreprocessor() {
}

void WavePreprocessor::deleteSielienceFromBeginningAndEnd(NormalizedSamplesList & sampleList) {

	WaveFileAnalizator analizator;
	double amplitude = analizator.findAmplitude(sampleList);
	double percentSilence = 5.0/100; // TODO: proposal: introduce percentSilence as a parameter of this method with default value
	uint32_t sampleCounter = 0;
		for (uint32_t i = 0; i < sampleList.getNumberOfSamples(); ++i) {
			double sample = sampleList.getSample(i);
			if (abs(sample) > amplitude*percentSilence) {
				++sampleCounter;
			}
		}

	double * dataFixed = new double [sampleCounter];

	sampleCounter = 0;
	for (uint32_t i = 0; i < sampleList.getNumberOfSamples(); ++i) {
				double sample = sampleList.getSample(i);
				if (abs(sample) > amplitude*percentSilence) {
					dataFixed[++sampleCounter] = sampleList.getSample(i);
				}
			}
	sampleList.setSampleListData(sampleCounter+1,dataFixed);
}

void WavePreprocessor::normalize(WaveFile waveFile) {
}
