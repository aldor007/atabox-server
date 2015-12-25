/*
 * ProcessAndAnalyze.cpp
 *
 *  Created on: 8 cze 2014
 *      Author: aldor
 */

#include "FeatureExtractor.h"


/*PROPERTY*/
#include "wave/analysis/AmplitudeProperty.h"
#include "wave/analysis/LengthProperty.h"
#include "wave/analysis/ZeroCrossingsProperty.h"
#include "wave/analysis/PercentageAboveProperty.h"
#include "wave/analysis/WhereIsAmplitudeProperty.h"
#include "wave/analysis/AverageValueProperty.h"
#include "wave/analysis/MfccProperty.h"

/*FILTER*/

#include "wave/processing/preprocessing/SilenceCuttingFilter.h"
#include "wave/processing/preprocessing/NormalizingFilter.h"

#include "wave/processing/postprocessing/HannWindowFilter.h"
#include "wave/processing/postprocessing/FastFourierTransformFilter.h"

FeatureExtractor::FeatureExtractor() {
}

void FeatureExtractor::init() {
    Processor * firstProcessor = new Processor();
    firstProcessor->addToFilterChain(new NormalizingFilter(1.0));
    firstProcessor->addToFilterChain(new SilenceCuttingFilter(0.2));
    SamplesAnalyzer * firstAnalizator = new SamplesAnalyzer();
    int step = 10;
    for (int i = 0; i < 100; i += step) {
        firstAnalizator->addProperty(new AmplitudeProperty(i, i + step));
        firstAnalizator->addProperty(new PercentageAboveProperty(0.01 * i));
        firstAnalizator->addProperty(new ZeroCrossingsProperty(i, i + step));
        firstAnalizator->addProperty(new AverageValueProperty(i, i + step));
    }
    firstAnalizator->addProperty(new LengthProperty());
    firstAnalizator->addProperty(new WhereIsAmplitudeProperty());
    firstAnalizator->addProperty(new MfccProperty());
    this->add(std::make_pair(firstProcessor, firstAnalizator));

}
void FeatureExtractor::add(std::pair<Processor*, SamplesAnalyzer *> item) {
    m_list.push_back(item);

}
jsonextend FeatureExtractor::getSummary(Samples & samples) {
    jsonextend result;
    for (int i = 0; i < m_list.size(); i++) {
        if (m_list[i].first != nullptr)
            m_list[i].first->applyFilterChainOn(samples);
         if (m_list[i].second != nullptr)
             result  += m_list[i].second->getPropertiesSummary(samples);

    }
    return result;
}

FeatureExtractor::~FeatureExtractor() {
}

