//
// Created by aldor on 20.12.15.
//

#include <utils/atabox_log.h>
#include "DBN.h"

const RBMConfig DBN::DEFAULT_CONFIG = {};

DBN::DBN(uint32_t numberOfInputs, std::valarray<size_t> hiddenSizes, uint32_t numberOfOutputs, const RBMConfig &config) : m_rbms(hiddenSizes.size() + 1) {
    RBMConfig firstConfig = config;
    firstConfig.numberOfVisible = numberOfInputs;
    firstConfig.numberOfHidden = hiddenSizes[0];
    LOG(debug) << "First config " << firstConfig << " config " << config;
    m_firstRBM = new RBM<shark::GaussianBinaryRBM, shark::GaussianBinaryPCD>(firstConfig);
    RBMConfig &prevConfig = firstConfig;

    for (size_t i = 0, j = 0, len = hiddenSizes.size(); i < len; ++i) {
        RBMConfig local = config;
        local.numberOfVisible = prevConfig.numberOfHidden;
        local.numberOfHidden = hiddenSizes[i];
        prevConfig = local;
        m_rbms[j++] = new RBM<shark::BinaryRBM, shark::BinaryPCD>(local);
    }
    RBMConfig endConfig = prevConfig;
    endConfig.numberOfVisible = prevConfig.numberOfHidden;
    endConfig.numberOfHidden = numberOfOutputs;
    m_rbms[hiddenSizes.size()] = new RBM<shark::BinaryRBM, shark::BinaryPCD>(endConfig);
    m_dataLen = 0;
}

DBN::~DBN() {

    delete m_firstRBM;
    for (uint16_t i = 0, len = m_rbms.size(); i < len; i++) {
        delete m_rbms[i];
    }
}

void DBN::setData(std::valarray<jsonextend>) {

}

shark::RealVector DBN::getOutput() {
    return m_rbms[m_rbms.size() - 1]->getHiddenLaverParameters();
}

void DBN::init(std::string path) {
    if (std::ifstream(path)) {
        std::ifstream in(path);
        shark::TextInArchive inArch(in);
        m_firstRBM->m_rbm.read(inArch);
        for (uint16_t i= 0; i < m_rbms.size(); ++i) {
            m_rbms[i]->m_rbm.read(inArch);
        }
        m_dataLen = m_firstRBM->m_rbm.visibleNeurons().size();
    } else {
        LOG(error) << "File " << path << " doesn't exist";
    }

}

void DBN::store(std::string path) {
    std::ofstream out(path);
    shark::TextOutArchive outArch(out);
    m_firstRBM->m_rbm.write(outArch);
    for (uint16_t i = 0; i < m_rbms.size(); ++i) {
        m_rbms[i]->m_rbm.write(outArch);
    }
}

void DBN::train(const std::valarray<jsonextend> &data) {
}

shark::RealVector DBN::predict(const jsonextend& json) {
    // normalizacja jsonextend a nie realvector w FeatureExtractor
    shark::RealVector data = std::move(json.toRealVector());
    predict(data);
}

shark::RealVector DBN::predict(const shark::RealVector &data) {
    shark::RealVector output, next;
    m_firstRBM->m_rbm.eval(data, next);
    m_rbms[0]->m_rbm.eval(next, output);
    next = output;
    size_t len = m_rbms.size() - 1;
    for (uint16_t i = 1; i < len; i++) {
        m_rbms[i]->m_rbm.eval(next, output);
        next = output;
    }

    m_rbms[len]->m_rbm.eval(next, output);
    return output;
}

void DBN::train(const std::valarray<shark::RealVector> &data) {
    size_t i = 0;
    size_t len;
    auto start = std::chrono::high_resolution_clock::now();
    m_dataLen = data[0].size();
    m_firstRBM->train(data);
    shark::RealVector input = m_firstRBM->getHiddenLaverParameters();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> fs = end - start;
    LOG(debug) << "Traning 0 took " << fs.count() << "s";
    for (auto it : input) {
        std::cout << it ;
    }
    std::cout << std::endl;

    for (len = m_rbms.size(); i < len; ++i) {
        LOG(debug) << "Training " << i + 1<< " input " << input.size();
        auto start = std::chrono::high_resolution_clock::now();
        m_rbms[i]->getHiddenLaverParameters();
        LOG(debug)<<m_rbms[i]->getConfig();
        m_rbms[i]->train(input);
        input = m_rbms[i]->getHiddenLaverParameters();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> fs = end - start;
        LOG(debug) << "Traning " << i + 1<< " took " << fs.count() << "s";

    }

}
