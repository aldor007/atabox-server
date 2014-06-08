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

webjs::value SamplesAnalizator::getPropertiesSummary(Samples& samples) {
    webjs::value result;

	for (int i = 0; i < properties.size(); ++i) {
			double value = properties[i]->getValue(samples);
			string name = properties[i]->getName();
			result[name] = webjs::value::number(value);
			// TODO collect JSON from this names and values and returns it
		}
	return result;
}
