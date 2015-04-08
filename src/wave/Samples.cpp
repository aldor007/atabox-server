/*
 * SampleList.cpp
 *
 *  Created on: 30 kwi 2014
 *      Author: mj
 */

#include <wave/Samples.h>

Samples::Samples(WaveFile & waveFile):
		Aquila::SignalSource(waveFile.getSamples(), waveFile.getNumberOfSamples(), waveFile.getSampleRate()) {
	int32_t maxOfRange = WaveUtils::getMaxOfRange(waveFile.getBitsPerSample());
	numberOfSamples = waveFile.getNumberOfSamples();
	this->sampleRate = waveFile.getSampleRate();
	lenghtInSeconds = WaveUtils::calculateLenghtInSeconds(numberOfSamples, this->sampleRate);
	decode(waveFile);

}

Samples::Samples(WaveFile && waveFile):
		Aquila::SignalSource(waveFile.getSamples(), waveFile.getNumberOfSamples(), waveFile.getSampleRate()) {

	numberOfSamples = waveFile.getNumberOfSamples();
	m_data.resize(numberOfSamples);
	this->sampleRate = waveFile.getSampleRate();
	lenghtInSeconds = WaveUtils::calculateLenghtInSeconds(numberOfSamples, this->sampleRate);
	decode(waveFile);
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
}

double& Samples::operator[](unsigned i)  {
	return m_data.at(i);
}

double Samples::operator[](unsigned i) const {
	return m_data.at(i);
}

double Samples::getSample(unsigned int i) const {
	return m_data[i];
}
std::complex<double> Samples::getSampleCx(unsigned int i) const {
	return m_data[i];
}

uint32_t Samples::getNumberOfSamples() const {
	return numberOfSamples;
}

double Samples::getLenghtInSeconds() const {
	return lenghtInSeconds;
}

void Samples::setSample(uint32_t index, double value) {
	m_data[index] = value;
}

void Samples::setSamplesData(double * data, unsigned int len) {
	m_data.clear();
	m_data.resize(len);
	m_data.assign(data, data + len);

}


