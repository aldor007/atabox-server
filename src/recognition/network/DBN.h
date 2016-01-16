//
// Created by aldor on 20.12.15.
//

#ifndef ATABOX_SERVER_DBN_H
#define ATABOX_SERVER_DBN_H

#include <vector>
#include "recognition/network/RBM.h"

class DBN {
public:
    DBN(std::vector<RBM::Config> &config);
    void setRBMConfig(RBM::Config config);


private:
    std::vector<RBM> m_rbms;
    std::vector<RBM::Config> m_rbmsConfig;

    void createDBN();
};

#endif //ATABOX_SERVER_DBN_H
