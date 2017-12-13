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
    DBN(uint32_t numberOfInputs, std::valarray<size_t> hiddenSizes, uint32_t numberOfOutputs, const RBMConfig &config = DBN::DEFAULT_CONFIG);
    ~DBN();
    void setData(std::valarray<jsonextend>);
    shark::RealVector getOutput();
    void init(std::string path = "/tmp/dbn.arch");
    void store(std::string path = "/tmp/dbn.arch");
    // find RealVector for given samples vector
    shark::RealVector predict(const jsonextend &data);
    void train(const std::valarray<jsonextend>& data);
    shark::RealVector predict(const shark::RealVector &data);
    void train(const std::valarray<shark::RealVector>& data);
private:
    std::valarray<RBM<shark::BinaryRBM, shark::BinaryPCD>*> m_rbms;
    RBM<shark::GaussianBinaryRBM, shark::GaussianBinaryPCD> *m_firstRBM;
    static const RBMConfig DEFAULT_CONFIG;
    size_t m_dataLen;
};

#endif //ATABOX_SERVER_DBN_H
