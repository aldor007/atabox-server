//
// Created by aldor on 20.12.15.
//

#include "DBN.h"


void DBN::createDBN() {
    for (size_t i = 0, len = m_rbms.size(); i < len; ++i) {
        m_rbms[i].setConfig(m_rbmsConfig[i]);
    }
}

void DBN::setRBMConfig(RBM::Config config) {

}

DBN::DBN(std::vector<RBM::Config> &config) {

}
