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
	for (int i = 0; i < waveFile.getNumberOfSamples(); ++i) {
		int sample = waveFile.getSample(i);
		if (abs(sample) > result) {
			result = sample;
		}
	}
	return result;
}

int WaveFileAnalizator::countZeroCrossings(WaveFile& waveFile) {
	int result = 0;
	for (int i = 0; i < waveFile.getNumberOfSamples(); ++i) {
		int sample = waveFile.getSample(i);
		if (abs(sample) > result) {
			result = sample;
		}
	}
	return result;
}

