/*
 * WaveFileAnalizator.cpp
 *
 *  Created on: Apr 2, 2014
 *      Author: mj
 */

#include "WaveFileAnalizator.h"

WaveFileAnalizator::WaveFileAnalizator() {
	// TODO Auto-generated constructor stub

}

WaveFileAnalizator::~WaveFileAnalizator() {
	// TODO Auto-generated destructor stub
}

int WaveFileAnalizator::findAmplitude(WaveFile& waveFile) {
	int result = 0;
	for (unsigned int i = 0; i < waveFile.getNumberOfSamples(); ++i) {
		int sample = waveFile.getSample(i);
		if (abs(sample) > result) {
			result = sample;
		}
	}
	return result;
}

int WaveFileAnalizator::countZeroCrossings(WaveFile& waveFile) {
	int result = 0;
	for (unsigned int i = 0; i < waveFile.getNumberOfSamples() - 1; ++i) {
		int sample = waveFile.getSample(i);
		int nextSample = waveFile.getSample(i + 1);
		if (sample * nextSample <= 0) {
			++result;
		}
	}
	return result;
}

int WaveFileAnalizator::maxOfRange(WaveFile& waveFile) {
	unsigned int bitPerSample = waveFile.getBitsPerSample();
	unsigned int result = (1 << (bitPerSample - 1)) - 1;
	return result;

}

double WaveFileAnalizator::percentageAbove(WaveFile& waveFile,
		double percentOfMax) {
	int aboveCounter = 0;
	int allCounter = 0;
	int threshold = percentOfMax * maxOfRange(waveFile);
	for (unsigned int i = 0; i < waveFile.getNumberOfSamples(); ++i) {
		++allCounter;
		int sample = waveFile.getSample(i);
		if (abs(sample) > threshold) {
			++aboveCounter;
		}
	}

	return aboveCounter * 1.0 / allCounter;
}

double WaveFileAnalizator::percetnageBelow(WaveFile& waveFile,
		double percentOfMax) {
	return 1.0 - percentageAbove(waveFile, percentOfMax);
}

WaveProperties WaveFileAnalizator::getAllProperties(WaveFile waveFile) {
	//TODO not yet implemented
}

