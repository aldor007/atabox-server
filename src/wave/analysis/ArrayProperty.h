//
// Created by Marcin Kaciuba on 09.05.2016.
//

#ifndef ATABOX_SERVER_ARRAYPROPERTY_H
#define ATABOX_SERVER_ARRAYPROPERTY_H

#include "wave/analysis/Property.h"


class ArrayProperty: public Property{
public:
    virtual shark::RealVector getRealVector(const Samples &) {
        return shark::RealVector();
    }

    virtual std::vector<double> getVector(const Samples &) {
        return std::vector<double>();
    }

};


#endif //ATABOX_SERVER_ARRAYPROPERTY_H
