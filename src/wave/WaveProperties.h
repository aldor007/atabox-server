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
	int aplitude;
	int zeroCrossings;
	double percentageAbove90percentage;
	double percentageAbove80percentage;
	double percentageAbove70percentage;
	double percentageAbove60percentage;
	double percentageAbove50percentage;
	double percentageAbove40percentage;
	double percentageAbove30percentage;
	double percentageAbove20percentage;
	double percentageAbove10percentage;

};

#endif /* WAVEPROPERTIES_H_ */
