//
// Created by aldor on 12.09.15.
//
#include <random>

#include <shark/Data/Dataset.h>

#include "RBM.h"
#include "wave/analysis/MfccProperty.h"


 std::ostream& operator<<(std::ostream& os, const RBM::Config& c) {
     os << "h = " << c.numberOfHidden << " v = " << c.numberOfVisible << " batchSize " << c.batchSize;
     return os;
 }


RBM::RBM(RBM::Config &config): m_rbm(shark::Rng::globalRng), m_cd(&m_rbm) {
    m_config = config;
    m_rbm.setStructure(config.numberOfVisible, config.numberOfHidden);
    m_cd.setK(config.numberOfKSteps);

    m_optimizer.setMomentum(config.momentum);
    m_optimizer.setLearningRate(config.learningRate);
}

RBM::RBM(const std::valarray<jsonextend> &data, size_t hidden):m_rbm(shark::Rng::globalRng), m_cd(&m_rbm) {
    m_config.numberOfHidden = hidden;
    m_cd.setK(m_config.numberOfKSteps);

    m_optimizer.setMomentum(m_config.momentum);
    m_optimizer.setLearningRate(m_config.learningRate);

    m_config.numberOfVisible = data[0].as_object().at(MfccProperty::NAME).as_array().size() + data[0].as_object().size();
    m_rbm.setStructure(m_config.numberOfVisible, m_config.numberOfHidden);
    m_config.batchSize = 1;
    setData(data);

}

// tutaj pwonno przekazywac sie duzo danych dla jednej osoby
// bo to jest raneg z batchami
void RBM::setData(const std::valarray<jsonextend> &propertiesArr) {
    // FIXME: get count of other features
    std::cout<<"Config "<<m_config<<std::endl;
    size_t properitesSize = propertiesArr[0].as_object().cend() - propertiesArr[0].as_object().cbegin();
    std::cout<<" propertiest size "<<properitesSize<<std::endl;
    size_t featuresSize = propertiesArr[0].as_object().at(MfccProperty::NAME).as_array().size() + propertiesArr[0].as_object().size();
    std::vector<shark::RealVector> data(propertiesArr.size(), shark::RealVector(m_config.numberOfVisible));
    std::cout<< " featuresSize = " << featuresSize << " arrsize ="<< propertiesArr.size()<<std::endl;
    size_t i = 0, j = 0;
    for (auto properties: propertiesArr) {
        j = 0;
        const auto mfccArr = properties.as_object().at(MfccProperty::NAME).as_array();

        for (auto iter = properties.as_object().cbegin(); iter != properties.as_object().cend(); ++iter) {
            if (j == featuresSize - 1) {
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
    // FIXME: to 1
    m_data = shark::createDataFromRange(data, m_config.batchSize);
    m_cd.setBatchSize(m_config.batchSize);
    m_cd.setData(m_data);
}


shark::RealVector RBM::getVisibleLayerParameters() {
    return m_rbm.visibleNeurons().parameterVector();
}

shark::RealVector RBM::getHiddenLaverParameters() {
    return m_rbm.hiddenNeurons().parameterVector();
}

void RBM::initializeWeights() {
    std::cout<<" number of params "<<m_rbm.numberOfParameters()<<std::endl;
    shark::RealVector weights(m_rbm.numberOfParameters());
    for(size_t i = 0; i != weights.size(); ++i) {
        weights(i) = shark::Rng::uni(-0.1,0.1);
    }
    m_rbm.setParameterVector(weights);
}

void RBM::learn() {
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
}
