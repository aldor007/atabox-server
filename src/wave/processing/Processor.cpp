/*
 * WavePreprocessor.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "wave/processing/Processor.h"

Processor::Processor() {

}

Processor::~Processor() {
}

void Processor::addToFilterChain(Filter& filter) {
	filters.push_back(&filter);
}
void Processor::addToFilterChain(Filter* filter) {
	filters.push_back(filter);
}

void Processor::applyFilterChainOn(Samples& samples) {
	for (int i = 0; i < filters.size(); ++i) {
		filters[i]->applyOn(samples);
	}
}
