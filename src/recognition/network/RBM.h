//
// Created by aldor on 12.09.15.
//

#ifndef ATABOX_SERVER_RBM_H
#define ATABOX_SERVER_RBM_H
#include <cstddef>

//used for training the RBM
#include <shark/Unsupervised/RBM/GaussianBinaryRBM.h>
#include <shark/Unsupervised/RBM/BinaryRBM.h>
#include <shark/Algorithms/GradientDescent/SteepestDescent.h>
#include <shark/Unsupervised/RBM/analytics.h>

#include <recognition/network/RBMConfig.h>
#include "wave/analysis/MfccProperty.h"
#include "utils/atabox_log.h"
#undef U
//for evaluation
#include <utils/jsonextend.h>
class DBN;


template <class R, class CD>
class RBM {
    friend  class DBN;
public:
    ~RBM() { }
    RBM();
    RBM(RBMConfig &config);
    // RBM(const std::valarray<jsonextend> &data, size_t numHidden);

    void setConfig(RBMConfig &config);
    RBMConfig getConfig();
    void train(const std::valarray<jsonextend> &data);
    void train(const std::valarray<shark::RealVector> &data);
    void train(const std::vector<shark::RealVector> &data);
    void train(shark::RealVector);
    void store(std::string path = "/tmp/rbm.arch");
    void init(std::string path = "/tmp/rbm.arch");

    shark::RealVector getVisibleLayerParameters();
    shark::RealVector getHiddenLaverParameters();
    shark::RealVector getParametersVector();
    shark::RealVector predict(shark::RealVector input);

private:
    void initializeWeights();
    void train();
    void convertData(const std::valarray<jsonextend> &data);

    R m_rbm;
    CD m_cd;
    shark::SteepestDescent m_optimizer;
    RBMConfig m_config;
    shark::UnlabeledData<shark::RealVector> m_data;
};

template<class R, class CD>
RBM<R, CD>::RBM(RBMConfig &config): m_rbm(shark::Rng::globalRng), m_cd(&m_rbm), m_config(config) {
    setConfig(config);
}

template<class R, class CD>
RBM<R, CD>::RBM(): m_rbm(shark::Rng::globalRng), m_cd(&m_rbm)  {
}

// tutaj pwonno przekazywac sie duzo danych dla jednej osoby
// bo to jest raneg z batchami
template<class R, class CD>
void RBM<R, CD>::convertData(const std::valarray<jsonextend> &propertiesArr) {

    if (propertiesArr.size() == 0) {
        LOG(debug) << "Empty properties array!";
        return;
    }

    size_t properitesSize = propertiesArr[0].as_object().cend() - propertiesArr[0].as_object().cbegin();
    size_t featuresSize = propertiesArr[0].as_object().at(MfccProperty::NAME).as_array().size() + propertiesArr[0].as_object().size();
    std::vector<shark::RealVector> data(propertiesArr.size(), shark::RealVector(m_config.numberOfVisible));

    LOG(debug) << "RBM feature size " << featuresSize;
    LOG(debug) << " Config " << m_config;

    for (auto properties: propertiesArr) {
        data.push_back(properties.toRealVector());
    }
    shark::UnlabeledData<shark::RealVector> unlabeledData = shark::createDataFromRange(data, m_config.batchSize);
    m_cd.setData(std::move(unlabeledData));
}

template<class R, class CD>
shark::RealVector RBM<R, CD>::getVisibleLayerParameters() {
    return m_rbm.visibleNeurons().parameterVector();
}

template<class R, class CD>
shark::RealVector RBM<R, CD>::getParametersVector() {
    return m_rbm.parameterVector();
}

template<class R, class CD>
shark::RealVector RBM<R, CD>::getHiddenLaverParameters() {
    return m_rbm.hiddenNeurons().parameterVector();
}

template<class R, class CD>
void RBM<R, CD>::initializeWeights() {
    shark::RealVector weights(m_rbm.numberOfParameters());
    for(size_t i = 0; i != weights.size(); ++i) {
        // weights(i) = shark::Rng::gauss(0.0, 1.0) * .1;
        weights(i) = shark::Rng::uni(-4. * std::sqrt(6. / (m_config.numberOfHidden + m_config.numberOfVisible)),
                                                     4. * std::sqrt(6. / (m_config.numberOfHidden + m_config.numberOfVisible)));

    }
    m_rbm.setParameterVector(weights);
}

template<class R, class CD>
void RBM<R, CD>::train(const std::valarray<jsonextend> &data) {
    convertData(data);
    train();
}

template<class R, class CD>
void RBM<R, CD>::train(const std::valarray<shark::RealVector> &data) {
    std::vector<shark::RealVector> local(data.size());
    local.assign(std::begin(data), std::end(data));

    shark::UnlabeledData<shark::RealVector> unlabeledData = shark::createDataFromRange(local, m_config.batchSize);
    m_cd.setData(std::move(unlabeledData));
    train();
}

template<class R, class CD>
void RBM<R, CD>::train(const std::vector<shark::RealVector> &data) {

    shark::UnlabeledData<shark::RealVector> unlabeledData = shark::createDataFromRange(data, m_config.batchSize);
    m_cd.setData(std::move(unlabeledData));
    train();
}

template<class R, class CD>
void RBM<R, CD>::train(shark::RealVector input) {
    shark::UnlabeledData<shark::RealVector> data{1, input, m_config.batchSize};
    m_data = data;
    m_cd.setData(data);
    train();
}

template<class R, class CD>
void RBM<R, CD>::train() {
    double logLikelyHood = 0.0;
    m_optimizer.init(m_cd);
    // m_rbm.evaluationType(true, false);
    for (uint16_t trail = 0; trail < m_config.numberOfTrails; ++trail) {
        // initializeWeights();

        for (uint16_t it = 0; it < m_config.numberOfIteration; ++it) {
            m_optimizer.step(m_cd);
            if(it % 2000 == 0){
                //std::cout<<partitionFunction(rbm);
                m_rbm.setParameterVector(m_optimizer.solution().point);
                logLikelyHood = shark::negativeLogLikelihood(m_rbm,m_data);
                std::cout<<it<<" "<<logLikelyHood<<std::endl;
                std::cout << "solution "<<  m_optimizer.solution().point.size() << " "<< m_optimizer.solution().value << '\n';
            }
        }
    }
    std::cout << "solution "<<  m_optimizer.solution().point.size() << " "<< m_optimizer.solution().value << '\n';

}


template<class R, class CD>
void RBM<R, CD>::setConfig(RBMConfig &config) {
    m_config = config;
    LOG(info) << "Set config " << config;
    m_rbm.setStructure(config.numberOfVisible, config.numberOfHidden);

    m_cd.setK(config.numberOfKSteps);
    // m_cd.setBatchSize(m_config.batchSize);

    m_optimizer.setMomentum(config.momentum);
    m_optimizer.setLearningRate(config.learningRate);

    initializeWeights();
}

template<class R, class CD>
RBMConfig RBM<R, CD>::getConfig() {
    return m_config;
}

template<class R, class CD>
shark::RealVector RBM<R, CD>::predict(shark::RealVector input) {
    shark::RealVector  output;
    m_rbm.evaluationType(true, false);
    m_rbm.eval(input, output);
    return output;
}

template<class R, class CD>
void RBM<R, CD>::store(std::string path) {
    std::ofstream out(path);
    shark::TextOutArchive outArch(out);
    m_rbm.write(outArch);
}

template<class R, class CD>
void RBM<R, CD>::init(std::string path) {
    std::ifstream in(path);
    shark::TextInArchive inArchive(in);
    m_rbm.read(inArchive);
}

#endif //ATABOX_SERVER_RBM_H
