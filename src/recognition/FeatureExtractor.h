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

#include "wave/analysis/SamplesAnalyzer.h"


class FeatureExtractor {
private:
	std::vector<std::pair<Processor*, SamplesAnalyzer *>> m_list;
public:
	FeatureExtractor();
	void init();
	void add(std::pair<Processor*, SamplesAnalyzer *> item);
	jsonextend getSummary(Samples & samples);
	shark::RealVector getSummaryRealVector(Samples &samples);
	std::vector<double> getSummaryVector(Samples &&samples);
	std::vector<double> getSummaryVector(Samples &samples);
	virtual ~FeatureExtractor();
};

#endif /* PROCESSANDANALYZE_H_ */
