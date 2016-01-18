//
// Created by aldor on 20.12.15.
//

#ifndef ATABOX_SERVER_DBN_H
#define ATABOX_SERVER_DBN_H

#undef U
#include <vector>
#include "recognition/network/RBM.h"

class DBN {
public:
    DBN(uint32_t numberOfInputs, std::valarray<size_t> hiddenSizes, uint32_t numberOfOutputs, const RBM::Config &config = DBN::DEFAULT_CONFIG);
    void setData(std::valarray<jsonextend>);

private:
    std::vector<RBM*> m_rbms;
    static const RBM::Config DEFAULT_CONFIG;
};

#endif //ATABOX_SERVER_DBN_H
