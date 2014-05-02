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
	static uint32_t getMaxOfRange(unsigned int bitsPerSample);

};

#endif /* WAVEUTILS_H_ */
