#ifndef MFCC_PROPERTY_H
#define MFCC_PROPERTY_H

#include <exception>
#include <vector>
#include <iostream>

#include <transform/Mfcc.h>
#include <transform/FftFactory.h>

#include "Property.h"
#include "utils/ataboxexception.h"

class MfccProperty: public Property
{
public:
    MfccProperty() {

    }
   virtual ~MfccProperty() {

    }
    
    virtual jsonextend getJSON(const Samples& samples) {

        Aquila::Mfcc mfcc(samples.getNumberOfSamples(), Aquila::FftFactory::Method::KISS);

        std::vector<double> mfccValues = mfcc.calculate(samples);

        json::value val;
        for (int i = 0, len = mfccValues.size(); i < len; ++i) {
            val[i] = mfccValues[i];
        }
        jsonextend value;
        value[getName()] = val;
        return value;
    }

    virtual std::string getName() {
        return "mfcc";
    }

    virtual double getValue(const Samples&) {
        throw ataboxException("Unsupported method!");
    }




    
};






#endif // MFCC_PROPERTY_H


