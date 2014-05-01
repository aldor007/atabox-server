/*
 * WaveProperties.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "WaveProperties.h"
#include <cpprest/json.h>
#include <sstream>

WaveProperties::WaveProperties() {
	// TODO Auto-generated constructor stub

}

WaveProperties::WaveProperties(std::string data) {
	// TODO Auto-generated constructor stub

}

WaveProperties::~WaveProperties() {
	// TODO Auto-generated destructor stub
}


std::string WaveProperties::toString() {

	json::value result = this->toJSON();
	return result.to_string(); //XXX:to_string works as_string doesn't
}

json::value WaveProperties::toJSON() {

	json::value result;
	result["amplitude"] = json::value::number(amplitude);
	result["name"] = json::value::string(name);
	result["zeroCrossings"] = json::value::number(zeroCrossings);
	result["percentageAbove90percentage"] = json::value::number(percentageAbove90percentage);
	result["percentageAbove90percentage"] = json::value::number(percentageAbove80percentage);
	result["percentageAbove70percentage"] = json::value::number(percentageAbove70percentage);
	result["percentageAbove60percentage"] = json::value::number(percentageAbove60percentage);
	result["percentageAbove50percentage"] = json::value::number(percentageAbove50percentage);
	result["percentageAbove40percentage"] = json::value::number(percentageAbove40percentage);
	result["percentageAbove30percentage"] = json::value::number(percentageAbove30percentage);
	result["percentageAbove20percentage"] = json::value::number(percentageAbove20percentage);
	result["percentageAbove10percentage"] = json::value::number(percentageAbove10percentage);
	return result;
}
