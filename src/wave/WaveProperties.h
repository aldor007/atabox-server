/*
 * WaveProperties.h
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#ifndef WAVEPROPERTIES_H_
#define WAVEPROPERTIES_H_

#include "cpprest/json.h"
class WaveProperties {
public:
	WaveProperties();
	WaveProperties(std::string data);
	WaveProperties(web::json::value data);
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
	std::string name = "commandName";
	std::string toString() const;
	web::json::value toJSON() const;
	bool operator<( const WaveProperties& other) const {
		//PropertiesComparator tmp;
		//double distance = tmp.getDistance(*this, other);
		return amplitude > other.amplitude;
	}
};

#endif /* WAVEPROPERTIES_H_ */
