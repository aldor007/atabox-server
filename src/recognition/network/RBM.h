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
#include <shark/Unsupervised/RBM/analytics.h>

class RBM {
   // RBM
public:
    struct Config {
        size_t numberOfHidden;
        size_t numberOfVisible;
        unsigned int numberOfKSteps = 1;
        double momentum = 0.5;
        double learningRate = 0.1;
    };
    virtual ~RBM() { }

    RBM(size_t numberOfHidden, size_t numberOfVisible);
    RBM(Config &config);
private:
    shark::GaussianBinaryRBM rbm;



};


#endif //ATABOX_SERVER_RBM_H
