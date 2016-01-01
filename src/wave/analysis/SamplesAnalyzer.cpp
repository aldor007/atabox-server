/*
 * WaveFileAnalizator.cpp
 *
 *  Created on: Apr 2, 2014
 *      Author: mj
 */

#include "SamplesAnalyzer.h"


SamplesAnalyzer::SamplesAnalyzer() {

}

SamplesAnalyzer::~SamplesAnalyzer() {
}


void SamplesAnalyzer::addProperty(Property& property) {
	properties.push_back(&property);
}
void SamplesAnalyzer::addProperty(Property* property) {
	properties.push_back(property);
}

jsonextend SamplesAnalyzer::getPropertiesSummary(Samples& samples) {
    jsonextend result;

	for (int i = 0; i < properties.size(); ++i) {
			result += properties[i]->getJSON(samples);
		}
	return result;
}
