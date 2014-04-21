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

double WaveFileAnalizator::findAmplitude(WaveFile& waveFile) {
	double result = 0;
	for (unsigned int i = 0; i < waveFile.getNumberOfSamples(); ++i) {
		double sample = waveFile.getSample(i);
		if (fabs(sample) > result) {
			result = sample;
		}
	}
	return result;
}

int WaveFileAnalizator::countZeroCrossings(WaveFile& waveFile) {
	int result = 0;
	for (unsigned int i = 0; i < waveFile.getNumberOfSamples() - 1; ++i) {
		double sample = waveFile.getSample(i);
		double nextSample = waveFile.getSample(i + 1);
		if (sample * nextSample <= 0) {
			++result;
		}
	}
	return result;
}
double WaveFileAnalizator::findPeriod(WaveFile& waveFile) {

	int result = 0;
	unsigned int i = 0;
	bool startCalt = true;
	unsigned int start = 0;
	for (i = 0; i < waveFile.getNumberOfSamples() - 1; ++i) {
		double sample = waveFile.getSample(i);
		double nextSample = waveFile.getSample(i + 1);

		if (sample * nextSample <= 0) {
			++result;
			if (startCalt) {
				startCalt = false;
				start = i;
			}
		}
		if (result == 3) {
			break;
		}
	}
	result = (i - start) / waveFile.getByteRate();

	return result;
}


double WaveFileAnalizator::percentageAbove(WaveFile& waveFile,
		double percentOfMax) {
	int aboveCounter = 0;
	int allCounter = 0;
	double threshold = percentOfMax * waveFile.getMaxOfRange();
	for (unsigned int i = 0; i < waveFile.getNumberOfSamples(); ++i) {
		++allCounter;
		double sample = waveFile.getSample(i);
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



WaveProperties WaveFileAnalizator::getAllProperties(WaveFile &waveFile) {
	//TODO not yet implemented
	WaveProperties result;
	result.amplitude = findAmplitude(waveFile);
	result.zeroCrossings = countZeroCrossings(waveFile);

	return result;
}

