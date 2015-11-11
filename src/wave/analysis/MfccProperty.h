#ifndef MFCC_PROPERTY_H
#define MFCC_PROPERTY_H

#include <exception>
#include <vector>
#include <iostream>

#include <transform/Mfcc.h>
#include <transform/FftFactory.h>
#include <source/FramesCollection.h>

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

        uint16_t samplesInFrame = std::ceil(FRAME_DURATION * samples.getSampleFrequency());
        Aquila::FramesCollection frames = Aquila::FramesCollection(samples, samplesInFrame);

        Aquila::Mfcc mfcc(samplesInFrame, Aquila::FftFactory::Method::KISS);

        json::value val;
        uint16_t counter = 0;
        for (auto it = frames.begin(); it != frames.end(); ++it) {
            std::vector<Aquila::SampleType> mfccValues = mfcc.calculate(*it);

            for (int i = 0, len = mfccValues.size(); i < len; ++i) {
                val[counter++] = mfccValues[i];
            }
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
    // duration of frame in s
    static const double FRAME_DURATION;


    
};
const double MfccProperty::FRAME_DURATION = 0.002;






#endif // MFCC_PROPERTY_H


