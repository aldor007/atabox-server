//
// Created by aldor on 20.12.15.
//

#include <utils/atabox_log.h>
#include "DBN.h"

const RBM::Config DBN::DEFAULT_CONFIG = {};

DBN::DBN(uint32_t numberOfInputs, std::valarray<size_t> hiddenSizes, uint32_t numberOfOutputs, const RBM::Config &config) : m_rbms(hiddenSizes.size()) {
    RBM::Config firstConfig = config;
    firstConfig.numberOfVisible = numberOfInputs;
    firstConfig.numberOfHidden = hiddenSizes[0];
    m_rbms[0] = new RBM(firstConfig);
    RBM::Config &prevConfig = firstConfig;

    for (size_t i = 1, len = hiddenSizes.size() - 1; i < len; ++i) {
        RBM::Config local = config;
        local.numberOfVisible = prevConfig.numberOfHidden;
        local.numberOfHidden = hiddenSizes[i];
        prevConfig = local;
        m_rbms[i] = new RBM(local);
    }
    RBM::Config endConfig = prevConfig;
    endConfig.numberOfVisible = prevConfig.numberOfHidden;
    endConfig.numberOfHidden = numberOfOutputs;
    m_rbms[hiddenSizes.size() - 1] = new RBM(endConfig);
}

void DBN::setData(std::valarray<jsonextend>) {

}

shark::RealVector DBN::getOutput() {
    return m_rbms[m_rbms.size() - 1]->getHiddenLaverParameters();
}

void DBN::init(std::string path) {
    // TODO: read weight for rbms
}

void DBN::train(const std::valarray<jsonextend> &data) {
    size_t i = 1;
    size_t len;
    auto start = std::chrono::high_resolution_clock::now();
    m_rbms[0]->train(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> fs = end - start;
    LOG(debug) << "Traning 0 took " << fs.count() << "s";
    for (len = m_rbms.size(); i < len; ++i) {
        LOG(debug) << "Training " << i << " layers " << len;
        auto start = std::chrono::high_resolution_clock::now();
        shark::RealVector input = m_rbms[i - 1]->getHiddenLaverParameters();
        LOG(debug)<<m_rbms[i]->getConfig();
        m_rbms[i]->train(shark::UnlabeledData<shark::RealVector>{input.size(), input, m_rbms[i]->getConfig().batchSize});
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> fs = end - start;
        LOG(debug) << "Traning " << i << " took " << fs.count() << "s";

    }

}

shark::RealVector DBN::predict(const jsonextend& json) {
    // normalizacja jsonextend a nie realvector w FeatureExtractor
    shark::RealVector data = std::move(json.covertToRealVector());
    shark::RealVector output, next;
    m_rbms[0]->m_rbm.eval(data, next);
    size_t len = m_rbms.size() - 1;
    for (uint16_t i = 1; i < len; i++) {
        m_rbms[i]->m_rbm.eval(next, output);
        next = output;
    }
    // m_rbms[len]->m_rbm.eval(next, output);
    return output;
}
