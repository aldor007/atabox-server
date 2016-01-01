//
// Created by aldor on 20.12.15.
//

#include "DBN.h"

DBN::DBN(size_t numberOfLayer, RBM::Config rbmConfig) : m_rbms(numberOfLayer, m_rbmConfig(rbmConfig) {
}

void DBN::createDBN() {
    for (size_t i = 0, len = m_rbms.size(); i < len; ++i) {
        m_rbms[i].setConfig(m_rbmConfig);
    }
}

DBN::DBN() {

}
