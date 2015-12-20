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
    virtual jsonextend getJSON(const Samples& samples) {

        uint16_t samplesInFrame = std::ceil(FRAME_DURATION * samples.getSampleFrequency());
        if (samplesInFrame < 1000) {
            samplesInFrame = 1000;
        }

        Aquila::FramesCollection frames = Aquila::FramesCollection(samples, samplesInFrame);

        Aquila::Mfcc mfcc(samplesInFrame, Aquila::FftFactory::Method::KISS);

        web::json::value val;
        uint16_t counter = 0;
        for (auto it = frames.begin(); it != frames.end(); ++it) {
            std::vector<Aquila::SampleType> mfccValues = mfcc.calculate(*it, MfccProperty::SIZE);

            for (int i = 0, len = mfccValues.size(); i < len; ++i) {
                val[counter++] = mfccValues[i];
            }
        }
        std::cout <<"Mfcc property "<<counter<<"samples "<<samplesInFrame<<"frames "<<frames.end() - frames.begin()<<std::endl;
        jsonextend value;
        value[getName()] = val;
        return value;
    }

    virtual std::string getName() {
        return MfccProperty::NAME;
    }

    virtual double getValue(const Samples&) {
        throw ataboxException("Unsupported method!");
    }

    // duration of frame in s
    static const double FRAME_DURATION;
    // property name
    static const char * NAME;
    // mfcc features size for one frame
    static const size_t SIZE = 12;
    // MAX frames
    static const size_t MAX_FRAME = 2000;


};


#endif // MFCC_PROPERTY_H


