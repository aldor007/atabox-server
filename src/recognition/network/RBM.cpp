//
// Created by aldor on 12.09.15.
//

#include "RBM.h"

RBM::RBM(size_t numberOfHidden, size_t numberOfVisible): m_rbm(shark::Rng::globalRng), m_cd(&m_rbm){
    m_rbm.setStructure(numberOfVisible, numberOfHidden);

    // m_optimizer.setMomentum(config.momentum);
   //  m_optimizer.setLearningRate(config.learningRate);
}

RBM::RBM(RBM::Config &config): m_rbm(shark::Rng::globalRng), m_cd(&m_rbm) {
    m_rbm.setStructure(config.numberOfVisible, config.numberOfHidden);
    m_cd.setK(config.numberOfKSteps);

    m_optimizer.setMomentum(config.momentum);
    m_optimizer.setLearningRate(config.learningRate);
}
