/*
 * WaveProperties.h
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#ifndef WAVEPROPERTIES_H_
#define WAVEPROPERTIES_H_

class WaveProperties {
public:
	WaveProperties();
	~WaveProperties();
	double amplitude = 0;
	int zeroCrossings = 0;
	double percentageAbove90percentage = 0.0;
	double percentageAbove80percentage = 0.0;
	double percentageAbove70percentage = 0.0;
	double percentageAbove60percentage = 0.0;
	double percentageAbove50percentage = 0.0;
	double percentageAbove40percentage = 0.0;
	double percentageAbove30percentage = 0.0;
	double percentageAbove20percentage = 0.0;
	double percentageAbove10percentage = 0.0;
	double period = 0;
	double frequency = 0;
	double lenghtInSeconds = 0.0;

};

#endif /* WAVEPROPERTIES_H_ */
