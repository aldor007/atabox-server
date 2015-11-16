//
// Created by aldor on 12.09.15.
//

#ifndef ATABOX_SERVER_RBM_H
#define ATABOX_SERVER_RBM_H
#include <cstddef>

//used for training the RBM
#include <shark/Unsupervised/RBM/BinaryRBM.h>
// #include <shark/Algorithms/GradientDescent/SteepestDescent.h>

//for evaluation
#include <utils/jsonextend.h>

class RBM {
   // RBM
public:
    struct Config {

        // number of hidden unit in RBM
        size_t numberOfHidden = 1;
        // number of visible unit in RBM
        size_t numberOfVisible = 1;
        // number of k-steps in Contrastive Divergence
        unsigned int numberOfKSteps = 1;
        // optimizer properties
        double momentum = 0.5;
        double learningRate = 0.1;
    };
    ~RBM() { }

    //RBM(size_t numberOfHidden, size_t numberOfVisible);
    //RBM(Config &config);

    //void setData(std::valarray<jsonextend> data);
private:
   /* shark::GaussianBinaryRBM m_rbm;
    shark::GaussianBinaryPCD m_cd;
    shark::SteepestDescent m_optimizer;
    shark::UnlabeledData<shark::RealVector> m_data;*/



};


#endif //ATABOX_SERVER_RBM_H
