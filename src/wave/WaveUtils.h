/*
 * WaveUtils.h
 *
 *  Created on: 2 maj 2014
 *      Author: mj
 */

#ifndef WAVEUTILS_H_
#define WAVEUTILS_H_
#include <stdint.h>

class WaveUtils {
public:
	WaveUtils();
	~WaveUtils();
	static uint32_t getMaxOfRange(uint16_t bitsPerSample);
	static double calculateLenghtInSeconds(uint32_t numberOfSamples, uint32_t sampleRate);
};

#endif /* WAVEUTILS_H_ */
