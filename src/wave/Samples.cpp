/*
 * SampleList.cpp
 *
 *  Created on: 30 kwi 2014
 *      Author: mj
 */

#include <wave/Samples.h>

Samples::Samples(WaveFile & waveFile):
		Aquila::SignalSource(waveFile.getSamples(), waveFile.getNumberOfSamples(), waveFile.getSampleRate()) {
	numberOfSamples = waveFile.getNumberOfSamples();
	lenghtInSeconds = WaveUtils::calculateLenghtInSeconds(numberOfSamples, m_sampleFrequency);
	decode(waveFile);

}

Samples::Samples(WaveFile && waveFile):
		Aquila::SignalSource(waveFile.getSamples(), waveFile.getNumberOfSamples(), waveFile.getSampleRate()) {

	numberOfSamples = waveFile.getNumberOfSamples();
	m_data.resize(numberOfSamples);
	lenghtInSeconds = WaveUtils::calculateLenghtInSeconds(numberOfSamples, m_sampleFrequency);
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
			m_data[i] = (atabox::SampleType) ((waveFile.getRawSample(i)-128) / maxOfRange);
		} else {
			m_data[i] = (atabox::SampleType) waveFile.getRawSample(i) / maxOfRange;
		}
	}


}
/**
 * Default contstrutor
 */
Samples::Samples():Aquila::SignalSource() {
}

Samples::~Samples() {
}

atabox::SampleType& Samples::operator[](unsigned i)  {
	return m_data.at(i);
}

atabox::SampleType Samples::operator[](unsigned i) const {
	return m_data.at(i);
}

atabox::SampleType Samples::getSample(unsigned int i) const {
	return m_data[i];
}
atabox::ComplexType Samples::getSampleCx(unsigned int i) const {
	return atabox::ComplexType{m_data[i]};
}

uint32_t Samples::getNumberOfSamples() const {
	return m_data.size();
}

double Samples::getLenghtInSeconds() const {
	return lenghtInSeconds;
}

void Samples::setSample(uint32_t index, atabox::SampleType value) {
	m_data[index] = value;
}

void Samples::setSamplesData(const atabox::SampleType * data, unsigned int len, atabox::FrequencyType freq = 44000) {
	m_data.clear();
	m_data.resize(len);
	m_data.assign(data, data + len);
	this->lenghtInSeconds =
			WaveUtils::calculateLenghtInSeconds(len,  freq);
    m_sampleFrequency = freq;

}


void Samples::setSampleFrequency(atabox::FrequencyType freq) {
    m_sampleFrequency = freq;
}
