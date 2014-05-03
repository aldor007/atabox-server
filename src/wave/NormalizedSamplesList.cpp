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
	int maxOfRange = WaveUtils::getMaxOfRange(waveFile.getBitsPerSample());
	numberOfSamples = waveFile.getNumberOfSamples();
	lenghtInSeconds = WaveUtils::calculateLenghtInSeconds(numberOfSamples, waveFile.getSampleRate());
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

double NormalizedSamplesList::getSample(unsigned int i) {
	return samples[i];
}

uint32_t NormalizedSamplesList::getNumberOfSamples() {
	return numberOfSamples;
}

double NormalizedSamplesList::getLenghtInSeconds() {
	return lenghtInSeconds;
}

NormalizedSamplesList::NormalizedSamplesList() {

}
void NormalizedSamplesList::setSampleListData(uint32_t numberOfSamples,double * data) {
	if (this->samples != nullptr) {
			delete this->samples;
		}
	this->samples = data;
	this->numberOfSamples = numberOfSamples;
}
