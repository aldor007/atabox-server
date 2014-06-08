/*
 * ProcessAndAnalyze.h
 *
 *  Created on: 8 cze 2014
 *      Author: aldor
 */

#ifndef PROCESSANDANALYZE_H_
#define PROCESSANDANALYZE_H_
#include <vector>
#include <utility>

#include "utils/jsonextend.h"

#include "wave/processing/Processor.h"

#include "wave/analysis/SamplesAnalizator.h"


class ProcessAndAnalyze {
private:
	std::vector<std::pair<Processor, SamplesAnalizator>> m_list;
public:
	ProcessAndAnalyze();
	void add(std::pair<Processor, SamplesAnalizator> item);
	jsonextend getSummary(Samples & samples);
	virtual ~ProcessAndAnalyze();
};

#endif /* PROCESSANDANALYZE_H_ */
