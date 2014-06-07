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

void SamplesAnalizator::getPropertiesSummary(Samples& samples) {

	for (int i = 0; i < properties.size(); ++i) {
			double value = properties[i]->getValue(samples);
			string name = properties[i]->getName();
			// TODO collect JSON from this names and values and returns it
		}
}




















// TODO remove from this file everything below the line
// //////////////////////////////////////////////////////////////////////




double SamplesAnalizator::percentageAbove(Samples& samples,
		double percentOfMax) {
	int aboveCounter = 0;
	int allCounter = 0;

	for (unsigned int i = 0; i < samples.getNumberOfSamples(); ++i) {
		++allCounter;
		double sample = samples.getSample(i);
		if (fabs(sample) > percentOfMax) {
			++aboveCounter;
		}
	}

	return aboveCounter * 1.0 / allCounter;
}

double SamplesAnalizator::percetnageBelow(Samples& samples,
		double percentOfMax) {
	return 1.0 - percentageAbove(samples, percentOfMax);
}


