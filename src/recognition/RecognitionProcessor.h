//
// Created by aldor on 28.11.15.
//

#ifndef ATABOX_SERVER_RECOGNITIONPROCESSOR_H
#define ATABOX_SERVER_RECOGNITIONPROCESSOR_H


#include <recognition/network/RBM.h>
#include <dataproviders/BaseDataProvider.h>
#include <wave/Samples.h>
#include "FeatureExtractor.h"

class RecognitionProcessor {
    RecognitionProcessor(BaseDataProvider<std::string, std::string> *dp, RBM::Config &config,
                             FeatureExtractor m_analyser);
    ~RecognitionProcessor();

    void addData(std::string name, jsonextend data);
    std::string recognise(Samples &data);

    void process(std::string name, Samples& samples);

private:
    RBM m_rbm;
    BaseDataProvider<std::string, std::string> * m_dp;
    FeatureExtractor m_analyser;

};


#endif //ATABOX_SERVER_RECOGNITIONPROCESSOR_H