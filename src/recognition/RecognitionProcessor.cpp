//
// Created by aldor on 28.11.15.
//

#include "RecognitionProcessor.h"

RecognitionProcessor::~RecognitionProcessor() {
    delete m_dp;
}

RecognitionProcessor::RecognitionProcessor(BaseDataProvider<std::string, std::string> *dp, RBMConfig &config,
                                           FeatureExtractor m_analyser)
        :m_dp(dp), m_analyser(m_analyser) {
}

void RecognitionProcessor::addData(std::string name, jsonextend data) {
    m_dp->put(name, data.serialize());
}
/*
 * @TODO: robimy tak. z RBM dostaje kolejny wektor cech, który wrzucam do klasyfikatora, który mi go porównuje
 */

std::string RecognitionProcessor::recognise(Samples& data) {
    std::map<std::string, std::string> allSamples = m_dp->getAllKV();
    jsonextend properties = m_analyser.getSummary(data);
    std::valarray<jsonextend> networkData(allSamples.size() + 1);
}

void RecognitionProcessor::process(std::string name, Samples &samples) {

}
