//
// Created by aldor on 12.09.15.
//

#ifndef ATABOX_SERVER_RBM_H
#define ATABOX_SERVER_RBM_H
#include <cstddef>

//used for training the RBM
#include <shark/Unsupervised/RBM/GaussianBinaryRBM.h>
#include <shark/Algorithms/GradientDescent/SteepestDescent.h>

//for evaluation
#include <utils/jsonextend.h>

class RBM {
   // RBM
public:
    struct Config {

        // number of hidden units in RBM
        size_t numberOfHidden = 1;
        // number of visible units in RBM
        size_t numberOfVisible = 1;
        // number of k-steps in Contrastive Divergence
        unsigned int numberOfKSteps = 1;
        // optimizer properties
        double momentum = 0.5;
        double learningRate = 0.1;
        // size of batch to learn
        size_t batchSize = 32;
        uint16_t numberOfIteration = 1000;
        uint16_t numberOfTrails = 3;
        friend std::ostream& operator<<(std::ostream& os, const Config& c);
    };
    ~RBM() { }
    RBM();
    RBM(Config &config);
    RBM(const std::valarray<jsonextend> &data, size_t numHidden);

    void setData(const std::valarray<jsonextend> &data);

    void setConfig(Config &config);
    void learn();

    shark::RealVector getVisibleLayerParameters();
    shark::RealVector getHiddenLaverParameters();
private:
    void initializeWeights();

    shark::GaussianBinaryRBM m_rbm;
    shark::GaussianBinaryPCD m_cd;
    shark::SteepestDescent m_optimizer;
    shark::UnlabeledData<shark::RealVector> m_data;
    Config m_config;
};


#endif //ATABOX_SERVER_RBM_H
