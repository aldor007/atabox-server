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
	json::value tmpData = json::value::parse(data.c_str());
	amplitude = tmpData["amplitude"].as_double();
	name = tmpData["name"].as_string();
	zeroCrossings = tmpData["zeroCrossings"].as_double();
	percentageAbove90percentage = tmpData["percentageAbove90percentage"].as_double();
	percentageAbove80percentage = tmpData["percentageAbove80percentage"].as_double();
	percentageAbove70percentage = tmpData["percentageAbove70percentage"].as_double();
	percentageAbove60percentage = tmpData["percentageAbove50percentage"].as_double();
	percentageAbove50percentage = tmpData["percentageAbove50percentage"].as_double();
	percentageAbove40percentage = tmpData["percentageAbove40percentage"].as_double();
	percentageAbove30percentage = tmpData["percentageAbove30percentage"].as_double();
	percentageAbove20percentage = tmpData["percentageAbove20percentage"].as_double();
	percentageAbove10percentage = tmpData["percentageAbove10percentage"].as_double();
}
WaveProperties::~WaveProperties() {
	// TODO Auto-generated destructor stub
}


std::string WaveProperties::toString() const {

	json::value tmpData = this->toJSON();
	return tmpData.to_string(); //XXX:to_string works as_string doesn't
}

json::value WaveProperties::toJSON() const {

	json::value tmpData;
	tmpData["amplitude"] = json::value::number(amplitude);
	tmpData["name"] = json::value::string(name);
	tmpData["zeroCrossings"] = json::value::number(zeroCrossings);
	tmpData["percentageAbove90percentage"] = json::value::number(percentageAbove90percentage);
	tmpData["percentageAbove80percentage"] = json::value::number(percentageAbove80percentage);
	tmpData["percentageAbove70percentage"] = json::value::number(percentageAbove70percentage);
	tmpData["percentageAbove60percentage"] = json::value::number(percentageAbove60percentage);
	tmpData["percentageAbove50percentage"] = json::value::number(percentageAbove50percentage);
	tmpData["percentageAbove40percentage"] = json::value::number(percentageAbove40percentage);
	tmpData["percentageAbove30percentage"] = json::value::number(percentageAbove30percentage);
	tmpData["percentageAbove20percentage"] = json::value::number(percentageAbove20percentage);
	tmpData["percentageAbove10percentage"] = json::value::number(percentageAbove10percentage);
	return tmpData;
}
