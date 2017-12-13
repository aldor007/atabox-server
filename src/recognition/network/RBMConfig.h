//
// Created by Marcin Kaciuba on 06.03.2016.
//

#ifndef ATABOX_SERVER_RBMCONFIG_H
#define ATABOX_SERVER_RBMCONFIG_H
struct RBMConfig {

    // number of hidden units in RBM
    size_t numberOfHidden = 1;
    // number of visible units in RBM
    size_t numberOfVisible = 1;
    // number of k-steps in Contrastive Divergence
    unsigned int numberOfKSteps = 1;
    // optimizer properties
    double momentum = 0.0;
    double learningRate = 0.1;
    // size of batch to learn
    size_t batchSize = 1;
    uint16_t numberOfIteration = 1000;
    uint16_t numberOfTrails = 3;
    friend std::ostream& operator<<(std::ostream& os, const RBMConfig& c);
};

#endif //ATABOX_SERVER_RBMCONFIG_H
