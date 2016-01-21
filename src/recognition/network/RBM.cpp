//
// Created by aldor on 12.09.15.
//
#include <random>

#include <shark/Data/Dataset.h>

#include "RBM.h"
#include "wave/analysis/MfccProperty.h"
#include "utils/atabox_log.h"


 std::ostream& operator<<(std::ostream& os, const RBM::Config& c) {
     os << "h = " << c.numberOfHidden << " v = " << c.numberOfVisible << " batchSize " << c.batchSize;
     return os;
 }


RBM::RBM(RBM::Config &config): m_rbm(shark::Rng::globalRng), m_cd(&m_rbm), m_config(config) {
    setConfig(config);
}

RBM::RBM(): m_rbm(shark::Rng::globalRng), m_cd(&m_rbm)  {
}

// tutaj pwonno przekazywac sie duzo danych dla jednej osoby
// bo to jest raneg z batchami
void RBM::convertData(const std::valarray<jsonextend> &propertiesArr) {

    size_t properitesSize = propertiesArr[0].as_object().cend() - propertiesArr[0].as_object().cbegin();
    size_t featuresSize = propertiesArr[0].as_object().at(MfccProperty::NAME).as_array().size() + propertiesArr[0].as_object().size();
    std::vector<shark::RealVector> data(propertiesArr.size(), shark::RealVector(m_config.numberOfVisible));

    m_config.numberOfVisible = propertiesArr[0].as_object().at(MfccProperty::NAME).as_array().size() + propertiesArr[0].as_object().size();
    m_rbm.setStructure(m_config.numberOfVisible, m_config.numberOfHidden);
    m_config.batchSize = 1;

    LOG(debug) << "RBM feature size " << featuresSize;
    LOG(debug) << " Config " << m_config;

    size_t i = 0, j = 0;
    for (auto properties: propertiesArr) {
        j = 0;
        const auto mfccArr = properties.as_object().at(MfccProperty::NAME).as_array();

        for (auto iter = properties.as_object().cbegin(); iter != properties.as_object().cend(); ++iter) {
            if (j == featuresSize - 1) {
                break;
            }

            // input should have only numberOfVisible
            if (j == m_config.numberOfVisible - 1) {
               break;
            }

            if (iter->first == MfccProperty::NAME) {
                data[i].resize(iter->second.as_array().size() + properitesSize);
                for (auto mfcc: iter->second.as_array()) {
                    data[i](j++) = mfcc.as_double();
                }

            } else  {
                if (iter->second.is_double())
                    data[i](j++) = iter->second.as_double();
                else if (iter->second.is_integer())
                    data[i](j++) = iter->second.as_integer();
            }
        }

        i++;
    }

    shark::UnlabeledData<shark::RealVector> unlabeledData = shark::createDataFromRange(data, m_config.batchSize);
    m_cd.setData(std::move(unlabeledData));
}

shark::RealVector RBM::getVisibleLayerParameters() {
    return m_rbm.visibleNeurons().parameterVector();
}

shark::RealVector RBM::getParametersVector() {
    return m_rbm.parameterVector();
}

shark::RealVector RBM::getHiddenLaverParameters() {
    return m_rbm.hiddenNeurons().parameterVector();
}

void RBM::initializeWeights() {
    shark::RealVector weights(m_rbm.numberOfParameters());
    for(size_t i = 0; i != weights.size(); ++i) {
        weights(i) = shark::Rng::uni(-0.1,0.1);
    }
    m_rbm.setParameterVector(weights);
}

void RBM::train(const std::valarray<jsonextend> &data) {
    convertData(data);
    train();
}

void RBM::train(shark::UnlabeledData<shark::RealVector> data) {
    m_cd.setData(data);
    train();
}

void RBM::train() {
    for (uint16_t trail = 0; trail < m_config.numberOfTrails; ++trail) {
        initializeWeights();
        m_optimizer.init(m_cd);

        for (uint16_t it = 0; it < m_config.numberOfIteration; ++it) {
            m_optimizer.step(m_cd);
        }
    }
}

void RBM::setConfig(RBM::Config &config) {
    m_config = config;
    m_rbm.setStructure(config.numberOfVisible, config.numberOfHidden);

    m_cd.setK(config.numberOfKSteps);
    m_cd.setBatchSize(m_config.batchSize);

    m_optimizer.setMomentum(config.momentum);
    m_optimizer.setLearningRate(config.learningRate);
}

RBM::Config RBM::getConfig() {
   return m_config;
}

