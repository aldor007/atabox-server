//
// Created by aldor on 20.12.15.
//

#ifndef ATABOX_SERVER_DBN_H
#define ATABOX_SERVER_DBN_H

#include <vector>
#include "recognition/network/RBM.h"

class DBN {
public:
    DBN(size_t numberOfLayer);
    void setRBMConfig(RBM::Config config);
    void pretrain();


private:
    std::vector<RBM> m_rbms;
    RBM::Config m_rbmConfig;
};

#endif //ATABOX_SERVER_DBN_H
