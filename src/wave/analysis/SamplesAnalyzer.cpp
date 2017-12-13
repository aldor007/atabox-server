/*
 * WaveFileAnalizator.cpp
 *
 *  Created on: Apr 2, 2014
 *      Author: mj
 */

#include <thread>
#include "SamplesAnalyzer.h"
#include <ctpl_stl.h>


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

	for (auto p: arrayProperties_) {
		result += p->getJSON(samples);
	}

	return result;
}

shark::RealVector SamplesAnalyzer::getProperties(Samples& samples) {
	shark::RealVector result;
	result = std::move(arrayProperties_.front()->getRealVector(samples));

	for (int i = 1, len = arrayProperties_.size(); i < len; ++i) {
		auto data = arrayProperties_[i]->getRealVector(samples);
		for (auto d: data) {
			result.push_back(d);
		}
	}

	for (int i = 0, len = properties.size(); i < len; ++i) {
		result.push_back(properties[i]->getValue(samples));
	}

	return result;
}

std::vector<double> SamplesAnalyzer::getPropertiesVector(Samples& samples) {
	std::vector<double> result;
	std::vector<std::thread> workers;
	std::vector<std::vector<double>> sync;
	sync.resize(arrayProperties_.size());
	ctpl::thread_pool pool{2};


	std::mutex mylock;
	for (int i = 0, len = properties.size(); i < len; ++i) {
		auto data =  properties[i]->getValue(samples);
		result.push_back(data);
	}

	for (int i = 0, len = arrayProperties_.size(); i < len; ++i) {
		pool.push([this, i, &sync, &mylock, &samples] (int tid){
			auto data = arrayProperties_[i]->getVector(samples);
			mylock.lock();
			sync[i] = data;
			mylock.unlock();
		});
	}

	pool.interrupt();

	for (int i = 0, len = sync.size(); i < len; ++i) {
		result.insert(result.end(), sync[i].begin(), sync[i].end());
	}

	return result;
}

void SamplesAnalyzer::addArrayProperty(ArrayProperty *property) {
	arrayProperties_.push_back(std::move(property));
}
