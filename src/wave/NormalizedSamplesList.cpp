/*
 * SampleList.cpp
 *
 *  Created on: 30 kwi 2014
 *      Author: mj
 */

#include <wave/NormalizedSamplesList.h>

NormalizedSamplesList::NormalizedSamplesList(WaveFile & waveFile) {
	try {
		samples = new double[waveFile.getNumberOfSamples()];
	} catch (std::bad_alloc) {
		throw "No memory";
	}
	int maxOfRange = getMaxOfRange(waveFile.getBitsPerSample());
	numberOfSamples = waveFile.getNumberOfSamples();
	for (uint32_t i = 0; i < numberOfSamples; i++) {
		if (waveFile.getBitsPerSample() == 8) {
			samples[i] = (double) (waveFile.getRawSample(i)-128 / maxOfRange);
		} else {
			samples[i] = (double) waveFile.getRawSample(i) / maxOfRange;
		}

	}

}

NormalizedSamplesList::~NormalizedSamplesList() {
	if (samples != nullptr) {
		delete samples;
		samples = nullptr;
	}
}

double NormalizedSamplesList::operator [](unsigned int i) {
	getSample(i);
}


/**
 * Returns max amplitude. This function is used because with different bit-per-sample factor it has different maximum values.
 * For example if we use 8-bits sample value 255 is maximum. When we use 32-bit sample value 255 is relatively small.
 * @param waveFile input file
 * @return maximum value
 */
uint32_t NormalizedSamplesList::getMaxOfRange(unsigned int bitsPerSample) {
	return (1 << (bitsPerSample - 1)) - 1;
}

double NormalizedSamplesList::getSample(unsigned int i) {
	return samples[i];
}

uint32_t NormalizedSamplesList::getNumberOfSamples() {
	return numberOfSamples;
}


NormalizedSamplesList::NormalizedSamplesList() {

}
