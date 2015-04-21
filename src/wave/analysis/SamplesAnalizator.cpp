/*
 * WaveFileAnalizator.cpp
 *
 *  Created on: Apr 2, 2014
 *      Author: mj
 */

#include "SamplesAnalizator.h"


SamplesAnalizator::SamplesAnalizator() {

}

SamplesAnalizator::~SamplesAnalizator() {
}


void SamplesAnalizator::addProperty(Property& property) {
	properties.push_back(&property);
}
void SamplesAnalizator::addProperty(Property* property) {
	properties.push_back(property);
}

jsonextend SamplesAnalizator::getPropertiesSummary(Samples& samples) {
    jsonextend result;

	for (int i = 0; i < properties.size(); ++i) {
			result += properties[i]->getJSON(samples);
		}
	return result;
}
