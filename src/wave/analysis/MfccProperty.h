#ifndef MFCC_PROPERTY_H
#define MFCC_PROPERTY_H

#include <exception>
#include <vector>
#include <iostream>

#include <transform/Mfcc.h>
#include <transform/FftFactory.h>
#include <source/FramesCollection.h>
#include <utils/atabox_log.h>

#include "Property.h"
#include "utils/ataboxexception.h"
#include "ArrayProperty.h"

class MfccProperty: public ArrayProperty {

public:
    virtual jsonextend getJSON(const Samples& samples) {

        uint16_t samplesInFrame = static_cast<uint16_t>(std::ceil(samples.getNumberOfSamples() / MfccProperty::MAX_FRAME));
        Aquila::FramesCollection frames = Aquila::FramesCollection(samples, samplesInFrame);

        Aquila::Mfcc mfcc(samplesInFrame, Aquila::FftFactory::Method::KISS);

        size_t numFeatures = std::round(MFCC_SIZE / frames.count());

        web::json::value val;
        uint16_t counter = 0;
        for (auto it = frames.begin(); it != frames.end(); ++it) {
            std::vector<Aquila::SampleType> mfccValues = mfcc.calculate(*it, numFeatures);

            for (size_t i = 0, len = mfccValues.size(); i < len; ++i) {
                val[counter++] = mfccValues[i];
            }
        }
        jsonextend value;
        value[getName()] = val;
        return value;
    }

    virtual shark::RealVector getRealVector(const Samples& samples) {

        uint16_t samplesInFrame = static_cast<uint16_t>(std::ceil(samples.getNumberOfSamples() / MfccProperty::MAX_FRAME));
        Aquila::FramesCollection frames = Aquila::FramesCollection(samples, samplesInFrame);

        Aquila::Mfcc mfcc(samplesInFrame, Aquila::FftFactory::Method::KISS);

        size_t numFeatures = std::round(MFCC_SIZE / frames.count());

        shark::RealVector result;
        uint16_t counter = 0;
        for (auto it = frames.begin(); it != frames.end(); ++it) {
            std::vector<Aquila::SampleType> mfccValues = mfcc.calculate(*it, numFeatures);

            for (size_t i = 0, len = mfccValues.size(); i < len; ++i) {
                result.push_back(mfccValues[i]);
            }
        }
        return result;
    }

    virtual std::vector<double> getVector(const Samples& samples) {


        uint16_t samplesInFrame = static_cast<uint16_t>(std::ceil(samples.getNumberOfSamples() / MfccProperty::MAX_FRAME));
        Aquila::FramesCollection frames = Aquila::FramesCollection(samples, samplesInFrame);

        Aquila::Mfcc mfcc(samplesInFrame, Aquila::FftFactory::Method::KISS);

        if (frames.count() == 0) {
            LOG(error) << "corupted data!";
            return std::vector<double>(0);
        }

        size_t numFeatures = std::round(MFCC_SIZE / frames.count());

        std::vector<double> result;
        uint16_t counter = 0;
        for (auto it = frames.begin(); it != frames.end(); ++it) {
            std::vector<Aquila::SampleType> mfccValues = mfcc.calculate(*it, /*numFeatures*/12);

            for (size_t i = 0, len = mfccValues.size(); i < len; ++i) {
                result.push_back(std::abs(mfccValues[i]));
            }
        }
        return result;
    }

    virtual std::string getName() {
        return MfccProperty::NAME;
    }

    virtual double getValue(const Samples&) {
        throw ataboxException("Unsupported method!");
    }

    // property name
    static const char * NAME;
    // MAX frames
    static const uint16_t MAX_FRAME = 9000;

    static const size_t MFCC_SIZE = 1000;
};


#endif // MFCC_PROPERTY_H


