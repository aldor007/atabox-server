//
// Created by aldor on 12.09.15.
//
#include <random>

#include <shark/Data/Dataset.h>

#include "RBM.h"
std::ostream& operator<<(std::ostream& os, const RBMConfig& c) {
    os << "h = " << c.numberOfHidden << " v = " << c.numberOfVisible << " batchSize " << c.batchSize;
    return os;
}


