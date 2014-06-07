/*
 * SampleList.cpp
 *
 *  Created on: 30 kwi 2014
 *      Author: mj
 */

#include <wave/Samples.h>

Samples::Samples(WaveFile & waveFile) {
	try {
		samples = new double[waveFile.getNumberOfSamples()];
	} catch (std::bad_alloc) {
		throw "No memory";
	}
	int32_t maxOfRange = WaveUtils::getMaxOfRange(waveFile.getBitsPerSample());
	numberOfSamples = waveFile.getNumberOfSamples();
	this->sampleRate = waveFile.getSampleRate();
	lenghtInSeconds = WaveUtils::calculateLenghtInSeconds(numberOfSamples, this->sampleRate);
	for (uint32_t i = 0; i < numberOfSamples; i++) {
		if (waveFile.getBitsPerSample() == 8) {
			samples[i] = (double) ((waveFile.getRawSample(i)-128) / maxOfRange);
		} else {
			samples[i] = (double) waveFile.getRawSample(i) / maxOfRange;
		}
	}

}

Samples::~Samples() {
	if (samples != nullptr) {
		delete samples;
		samples = nullptr;
	}
}

//TODO a jak ktos będzie chcial ustawiac tak wartosc? samples[5] = 3.3 - będzie się dziwić czemu nic się nie zmienia
double Samples::operator [](unsigned int i) {
	return getSample(i);
}

double Samples::getSample(unsigned int i) {
	return samples[i];
}

uint32_t Samples::getNumberOfSamples() {
	return numberOfSamples;
}

double Samples::getLenghtInSeconds() {
	return lenghtInSeconds;
}

void Samples::setSample(uint32_t index, double value) {
	samples[index] = value;
}

Samples::Samples() {

}

void Samples::setSampleListData(uint32_t numberOfSamples, double * data) {
	if (this->samples != nullptr) {
			delete this->samples;
		}
	this->samples = data;
	this->numberOfSamples = numberOfSamples;
	this->lenghtInSeconds =
			WaveUtils::calculateLenghtInSeconds(this->numberOfSamples, this->sampleRate);
}
