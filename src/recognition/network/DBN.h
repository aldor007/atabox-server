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

private:
    std::vector<RBM> m_rbms;
};

#endif //ATABOX_SERVER_DBN_H
