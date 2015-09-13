//
// Created by aldor on 12.09.15.
//

#include "RBM.h"

RBM::RBM(size_t numberOfHidden, size_t numberOfVisible): rbm(shark::Rng::globalRng) {
    rbm.setStructure(numberOfVisible, numberOfHidden);
}

RBM::RBM(RBM::Config &config): rbm(shark::Rng::globalRng) {
    rbm.setStructure(config.numberOfVisible, config.numberOfHidden);
}
