/*
 * WavePreprocessor.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "WavePreprocessor.h"
#include "WaveFileAnalizator.h"

WavePreprocessor::WavePreprocessor() {
	// TODO Auto-generated constructor stub

}

WavePreprocessor::~WavePreprocessor() {
	// TODO Auto-generated destructor stub
}

void WavePreprocessor::deleteSielienceFromBeginningAndEnd(WaveFile waveFile) {

	WaveFileAnalizator analizator;
	int amplitude = analizator.findAmplitude(waveFile);
	int percentSilence = 5/100;
	int sampleCounter = 0;
		for (unsigned int i = 0; i < waveFile.getNumberOfSamples(); ++i) {
			double sample = waveFile.getSample(i);
			if (abs(sample) > amplitude*percentSilence) {
				++sampleCounter;
			}
		}

}

void WavePreprocessor::normalize(WaveFile waveFile) {
}
