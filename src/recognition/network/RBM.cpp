//
// Created by aldor on 12.09.15.
//
#include <random>

#include <shark/Data/Dataset.h>

#include "RBM.h"
#include "wave/analysis/MfccProperty.h"


RBM::RBM(size_t numberOfHidden, size_t numberOfVisible): m_rbm(shark::Rng::globalRng), m_cd(&m_rbm){
    m_rbm.setStructure(numberOfVisible, numberOfHidden);

    m_optimizer.setMomentum(m_config.momentum);
    m_optimizer.setLearningRate(m_config.learningRate);
}

RBM::RBM(RBM::Config &config): m_rbm(shark::Rng::globalRng), m_cd(&m_rbm) {
    m_rbm.setStructure(config.numberOfVisible, config.numberOfHidden);
    m_cd.setK(config.numberOfKSteps);

    m_optimizer.setMomentum(config.momentum);
    m_optimizer.setLearningRate(config.learningRate);
}

// tutaj pwonno przekazywac sie duzo danych dla jednej osoby
// bo to jest raneg z batchami
void RBM::setData(std::valarray<jsonextend> propertiesArr) {
    // FIXME: get count of other features
    size_t featuresSize = propertiesArr[0].as_object().at(MfccProperty::NAME).size() + propertiesArr[0].as_object().size();
    std::vector<shark::RealVector> data(propertiesArr.size(), shark::RealVector(featuresSize*2));
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
                auto mfcc = iter->second.as_array();
                for (std::size_t k = 0; k != MfccProperty::SIZE; ++k) {
                    if (j == featuresSize - 1) {
                        break;
                    }
                    std::cout<<iter->first<<" "<<j<<std::endl;
                    data[i](j++) = mfcc[k].as_double();
                }

            } else  {
                std::cout<<iter->first<<" "<<j<<std::endl;
                if (iter->second.is_double())
                    data[i][j++] = iter->second.as_double();
                else if (iter->second.is_integer())
                    data[i][j++] = iter->second.as_integer();
            }
            i++;
        }

    }

    m_data = shark::createDataFromRange(data, m_config.batchSize);
    m_cd.setData(m_data);
}


shark::RealVector RBM::getVisibleLayerParameters() {
    return m_rbm.visibleNeurons().parameterVector();
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

void RBM::learn() {
    for (uint16_t trail = 0; trail < m_config.numberOfTrails; ++trail) {
        initializeWeights();
        m_optimizer.init(m_cd);

        for (uint16_t it = 0; it < m_config.numberOfIteration; ++it) {
            m_optimizer.step(m_cd);
        }
    }
}
