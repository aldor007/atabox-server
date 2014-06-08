/*
 * WavePreprocessor.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "Preprocessor.h"
#include "../analysis/SamplesAnalizator.h"

Preprocessor::Preprocessor() {

}

Preprocessor::~Preprocessor() {
}

void Preprocessor::addToFilterChain(Filter& filter) {
	filters.push_back(&filter);
}
void Preprocessor::addToFilterChain(Filter* filter) {
	filters.push_back(filter);
}

void Preprocessor::applyFilterChainOn(Samples& samples) {
	for (int i = 0; i < filters.size(); ++i) {
		filters[i]->applyOn(samples);
	}
}
