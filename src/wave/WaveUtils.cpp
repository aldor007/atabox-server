/*
 * WaveUtils.cpp
 *
 *  Created on: 2 maj 2014
 *      Author: mj
 */

#include <wave/WaveUtils.h>

WaveUtils::WaveUtils() {

}

WaveUtils::~WaveUtils() {
}

/**
 * Returns max amplitude. This function is used because with different bit-per-sample factor it has different maximum values.
 * For example if we use 8-bits sample value 127 is maximum. When we use 32-bit sample value 255 is relatively small.
 * @param waveFile input file
 * @return maximum value
 */
uint32_t WaveUtils::getMaxOfRange(uint16_t bitsPerSample) {
	return (1 << (bitsPerSample - 1)) - 1;
}

double WaveUtils::calculateLenghtInSeconds(uint32_t numberOfSamples,
		uint32_t sampleRate) {
	return (double)numberOfSamples / sampleRate;
}
