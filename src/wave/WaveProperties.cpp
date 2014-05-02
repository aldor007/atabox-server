/*
 * WaveProperties.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "WaveProperties.h"
#include <cpprest/json.h>

WaveProperties::WaveProperties() {
	// TODO Auto-generated constructor stub

}

WaveProperties::WaveProperties(std::string data) {
	// TODO Auto-generated constructor stub
	web::json::value tmpData = web::json::value::parse(data.c_str());
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

	web::json::value tmpData = this->toJSON();
	return tmpData.to_string(); //XXX:to_string works as_string doesn't
}

web::json::value WaveProperties::toJSON() const {

	web::json::value tmpData;
	tmpData["amplitude"] = web::json::value::number(amplitude);
	tmpData["name"] = web::json::value::string(name);
	tmpData["zeroCrossings"] = web::json::value::number(zeroCrossings);
	tmpData["percentageAbove90percentage"] = web::json::value::number(percentageAbove90percentage);
	tmpData["percentageAbove80percentage"] = web::json::value::number(percentageAbove80percentage);
	tmpData["percentageAbove70percentage"] = web::json::value::number(percentageAbove70percentage);
	tmpData["percentageAbove60percentage"] = web::json::value::number(percentageAbove60percentage);
	tmpData["percentageAbove50percentage"] = web::json::value::number(percentageAbove50percentage);
	tmpData["percentageAbove40percentage"] = web::json::value::number(percentageAbove40percentage);
	tmpData["percentageAbove30percentage"] = web::json::value::number(percentageAbove30percentage);
	tmpData["percentageAbove20percentage"] = web::json::value::number(percentageAbove20percentage);
	tmpData["percentageAbove10percentage"] = web::json::value::number(percentageAbove10percentage);
	return tmpData;
}
