//
// Created by aldor on 18.06.16.
//

#ifndef ATABOX_SERVER_LPCCPROPERTY_H
#define ATABOX_SERVER_LPCCPROPERTY_H

#include <utils/ataboxexception.h>
#include <transform/FftFactory.h>
#include <source/FramesCollection.h>

#include "ArrayProperty.h"
#include "MfccProperty.h"

class LpccProperty :public ArrayProperty {
    int order_ = 10;


public:
    virtual jsonextend getJSON(const Samples& samples) {
        jsonextend data;
        shark::RealVector real = getRealVector(samples);
        web::json::value val;
        uint16_t counter = 0;
        for (auto d: real) {
            val[counter++] = d;
        }
        data[getName()] = val;
        return data;
    }
    virtual std::vector<double> getVector(const Samples& samples) {
        std::vector<double> data;
        uint16_t samplesInFrame = static_cast<uint16_t>(std::ceil(samples.getNumberOfSamples() / MfccProperty::MAX_FRAME));
        size_t size = samplesInFrame;
        Aquila::FramesCollection frames{samples, samplesInFrame};
        data.resize((order_ + 1) * frames.count());
        // size_t sizeFFT = nextPowerTwo(2 * size);

        // std::vector<Aquila::SampleType> paddedSignal(samples.)
        size_t counter = 0;
        for (Aquila::Frame &frame: frames) {
            std::shared_ptr<Aquila::Fft> fft = Aquila::FftFactory::getFft(samplesInFrame, Aquila::FftFactory::KISS);
            Aquila::SpectrumType spectrum = fft->fft(frame.toArray());
            for (Aquila::ComplexType &s: spectrum) {
                s = Aquila::ComplexType(s.real() * s.real() + s.imag() * s.imag(), 0.0);
            }

            double * t = new double[size];
            fft->ifft(spectrum, t);

            // Levinson-Durbin algorithm
            std::vector<double> temp(order_);

            double k;
            double E = t[0];
            data[counter + 0] = 1;

            for (int i=1; i<(order_+1); i++) {
                k = t[i];

                for (int j=1; j<i; j++) {
                    k += t[i-j] * data[counter + j];
                }

                if (E == 0 || k == 0) {
                    break;
                }

                k /= E;

                //reflection[i-1] = k;
                data[counter + i] = -k;

                for (int j=1; j<i; j++) {
                    temp[j] = data[counter + j] - k*data[counter + i-j];
                }

                for (int j=1; j<i; j++) {
                    data[counter + j] = std::abs(temp[j]);
                }
                data[counter + i] = std::abs(data[counter + i]);

                E *= (1-k*k);
            }
            delete [] t;
            counter += order_ + 1;
        }
        return data;
    }

    virtual shark::RealVector getRealVector(const Samples& samples) {
        shark::RealVector data;
        uint16_t samplesInFrame = static_cast<uint16_t>(std::ceil(samples.getNumberOfSamples() / MfccProperty::MAX_FRAME));
        size_t size = samplesInFrame;
        Aquila::FramesCollection frames{samples, samplesInFrame};
        data.resize((order_ + 1) * frames.count());
        // size_t sizeFFT = nextPowerTwo(2 * size);

        // std::vector<Aquila::SampleType> paddedSignal(samples.)
        size_t counter = 0;
        for (Aquila::Frame &frame: frames) {
            std::shared_ptr<Aquila::Fft> fft = Aquila::FftFactory::getFft(samplesInFrame, Aquila::FftFactory::KISS);
            Aquila::SpectrumType spectrum = fft->fft(frame.toArray());
            for (Aquila::ComplexType &s: spectrum) {
                s = Aquila::ComplexType(s.real() * s.real() + s.imag() * s.imag(), 0.0);
            }

            double * t = new double[size];
            fft->ifft(spectrum, t);

            // Levinson-Durbin algorithm
            std::vector<double> temp(order_);

            double k;
            double E = t[0];
            data[counter + 0] = 1;

            for (int i=1; i<(order_+1); i++) {
                k = t[i];

                for (int j=1; j<i; j++) {
                    k += t[i-j] * data[counter + j];
                }

                if (k == 0) {
                    break;
                }

                k /= E;

                //reflection[i-1] = k;
                data[counter + i] = -k;

                for (int j=1; j<i; j++) {
                    temp[j] = data[counter + j] - k*data[counter + i-j];
                }

                for (int j=1; j<i; j++) {
                    data[counter + j] = std::abs(temp[j]);
                }

                E *= (1-k*k);
            }
            delete [] t;
            counter += order_ + 1;
        }
        return data;
    }

    virtual std::string getName() {
        return "lpcc";
    }

    virtual double getValue(const Samples&) {
        throw ataboxException("Unsupported method!");
    }

};


#endif //ATABOX_SERVER_LPCCPROPERTY_H
