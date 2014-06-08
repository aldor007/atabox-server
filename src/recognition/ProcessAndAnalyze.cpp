/*
 * ProcessAndAnalyze.cpp
 *
 *  Created on: 8 cze 2014
 *      Author: aldor
 */

#include <recognition/ProcessAndAnalyze.h>

ProcessAndAnalyze::ProcessAndAnalyze() {

}

void ProcessAndAnalyze::add(std::pair<Processor, SamplesAnalizator> item) {
	m_list.push_back(item);

}
jsonextend ProcessAndAnalyze::getSummary(Samples & samples) {
	jsonextend result;
	for (int i = 0; i < m_list.size(); i++) {
		//if (m_list[i].first != nullptr)
			m_list[i].first.applyFilterChainOn(samples);
		// if (m_list[i].second != nullptr)
			 result  += m_list[i].second.getPropertiesSummary(samples);

	}
	return result;


}
ProcessAndAnalyze::~ProcessAndAnalyze() {
}

