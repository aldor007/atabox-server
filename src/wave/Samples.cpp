/*
 * SampleList.cpp
 *
 *  Created on: 30 kwi 2014
 *      Author: mj
 */

#include <wave/Samples.h>
#include <numeric>


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
	return m_data[i];
}

atabox::SampleType Samples::operator[](unsigned i) const {
	return m_data[i];
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

std::vector<double> Samples::getData() {
	return m_data;
}

void Samples::draw(const char * str) {
	uint16_t len = m_data.size();
	uint16_t samplesPerPix = static_cast<uint16_t >(m_sampleFrequency/(m_sampleFrequency));
	if (samplesPerPix == 0) {
		samplesPerPix = 1;
	}

    size_t t = 0;
	std::vector<unsigned int> pixels;
	for (auto it = m_data.begin(); it < m_data.end() -  samplesPerPix; it += samplesPerPix) {
		double sum = std::accumulate(it, it + samplesPerPix, 0.0);
		//std::cout << "sum " << sum << " "<< sum/samplesPerPix <<"px " << sum/samplesPerPix * 500 +1025 << std::endl;
		pixels.push_back(std::ceil(sum/samplesPerPix * 500 + 525));
	}

	cimg_library::CImg<unsigned int> img{static_cast<unsigned int>(pixels.size()), 1050};
	const unsigned char color[] = { 255,128,64 };
	img.draw_line(0, 500, pixels.size(), 500, color);
//	for (auto x = pixels.begin(); x < pixels.end() - 1; x = x + 2) {
	for (auto x: pixels) {//} x < pixels.end() - 1; x = x + 2) {
		img.draw_point(t++, x, color);
		//img.draw_line(t++, *x, t++, *(x+1), color);
	}

	img.save_jpeg(str);
}

Samples Samples::createSample(WaveFile w) {
	return Samples(w);
}
