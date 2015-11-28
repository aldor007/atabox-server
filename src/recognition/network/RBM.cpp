//
// Created by aldor on 12.09.15.
//

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
   std::vector<shark::RealVector> data(propertiesArr.size(), shark::RealVector(MfccProperty::SIZE +  12));
    size_t i = 0, j = 0;
    for (auto properties: propertiesArr) {
        j = 0;
        const auto mfccArr = properties.as_object().at(MfccProperty::NAME).as_array();

        for (auto iter = properties.as_object().cbegin(); iter != properties.as_object().cend(); ++iter) {
            if (iter->first == MfccProperty::NAME) {
                auto mfcc =properties.as_object().at(MfccProperty::NAME);
                for (std::size_t k = 0; k != MfccProperty::SIZE; ++k) {
                    data[i](j++) = mfcc[k].as_double();
                }

            } else  {
                data[i][j++] = iter->second.as_double();
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

void RBM::learn() {



}
