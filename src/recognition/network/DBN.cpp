//
// Created by aldor on 20.12.15.
//

#include "DBN.h"

const RBM::Config DBN::DEFAULT_CONFIG = {};

DBN::DBN(uint32_t numberOfInputs, std::valarray<size_t> hiddenSizes, uint32_t numberOfOutputs, const RBM::Config &config) : m_rbms(hiddenSizes.size() + 1) {
    RBM::Config firstConfig = config;
    firstConfig.numberOfVisible = numberOfInputs;
    firstConfig.numberOfHidden = hiddenSizes[0];
    m_rbms[0] = new RBM(firstConfig);
    RBM::Config &prevConfig = firstConfig;

    for (size_t i = 1, len = hiddenSizes.size() - 1; i < len; ++i) {
        RBM::Config local = config;
        local.numberOfVisible = prevConfig.numberOfHidden;
        local.numberOfHidden = hiddenSizes[i];
        prevConfig = config;
        m_rbms[i] = new RBM(local);
    }
    RBM::Config endConfig = prevConfig;
    endConfig.numberOfVisible = numberOfOutputs;
    m_rbms[hiddenSizes.size() - 1] = new RBM(endConfig);
}

void DBN::setData(std::valarray<jsonextend>) {

}

shark::RealVector DBN::getOutput() {
    return (*m_rbms.end())->getHiddenLaverParameters();
}

void DBN::init(std::string path) {
    // TODO: read weight for rbms
}

shark::RealVector DBN::find(jsonextend data) {
    m_rbms[0]->setData({data});
    m_rbms[0]->learn();
    size_t i = 1;
    size_t len;
    for (len = m_rbms.size() - 1; i < len; ++i) {
        m_rbms[i]->setData(shark::Data<shark::RealVector>{1, m_rbms[i - 1]->getParametersVector()});
        m_rbms[i]->learn();
    }
    return this->getOutput();
}
