/*
 * SampleList.cpp
 *
 *  Created on: 30 kwi 2014
 *      Author: mj
 */

#include <wave/Samples.h>

Samples::Samples(WaveFile & waveFile) {
	int32_t maxOfRange = WaveUtils::getMaxOfRange(waveFile.getBitsPerSample());
	numberOfSamples = waveFile.getNumberOfSamples();
	this->sampleRate = waveFile.getSampleRate();
	lenghtInSeconds = WaveUtils::calculateLenghtInSeconds(numberOfSamples, this->sampleRate);
	decode();

}

Samples::Samples(WaveFile && waveFile) {

	numberOfSamples = waveFile.getNumberOfSamples();
	m_data.resize(numberOfSamples);
	this->sampleRate = waveFile.getSampleRate();
	lenghtInSeconds = WaveUtils::calculateLenghtInSeconds(numberOfSamples, this->sampleRate);
	decode();
}

/**
 * [Samples::decode raw chabnel data into audio channel]
 * @param waveFile [description]
 */
void Samples::decode(WaveFile &waveFile) {
	int32_t maxOfRange = WaveUtils::getMaxOfRange(waveFile.getBitsPerSample());
	for (uint32_t i = 0; i < numberOfSamples; i++) {
		if (waveFile.getBitsPerSample() == 8) {
			m_data[i] = (double) ((waveFile.getRawSample(i)-128) / maxOfRange);
		} else {
			m_data[i] = (double) waveFile.getRawSample(i) / maxOfRange;
		}
	}


}


Samples::~Samples() {
	if (samples != nullptr) {
		delete[] samples;
		samples = nullptr;
	}
}

//TODO a jak ktos będzie chcial ustawiac tak wartosc? samples[5] = 3.3 - będzie się dziwić czemu nic się nie zmienia
cx& Samples::operator [](unsigned int i) const{
	return samples[i];
}

double Samples::getSample(unsigned int i) const {
	return samples[i].real();
}
cx& Samples::getSampleCx(unsigned int i) const {
	return samples[i];
}

uint32_t Samples::getNumberOfSamples() const {
	return numberOfSamples;
}

double Samples::getLenghtInSeconds() const {
	return lenghtInSeconds;
}

void Samples::setSample(uint32_t index, double value) {
	samples[index] = value;
}

Samples::Samples() {

}
void Samples::setSampleListData(uint32_t numberOfSamples, cx * data) {
	if (this->samples != nullptr || this->numberOfSamples < numberOfSamples) {
			delete[] this->samples;
			this->samples = new cx[numberOfSamples];
		}
	else {
			this->samples = new cx[numberOfSamples];
	}
	std::memcpy(samples, data, numberOfSamples * sizeof(cx));

	this->numberOfSamples = numberOfSamples;
	this->lenghtInSeconds =
			WaveUtils::calculateLenghtInSeconds(this->numberOfSamples, this->sampleRate);
}
