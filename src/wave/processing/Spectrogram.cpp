//
// Created by aldor on 28.05.16.
//

#include <cmath>
#include <global.h>
#include <source/window/BlackmanWindow.h>
#include <shark/LinAlg/Base.h>
#include "Spectrogram.h"

Spectrogram::Spectrogram(const Samples &samples, float chunk, float overlap): data_(200 * 100){
    initColors();

    Aquila::SignalSource in{samples};
    size_t w = 200;
    size_t h = 100;
    in *= Aquila::BlackmanWindow{samples.getNumberOfSamples()};
    uint16_t samplesInFrame = 2048; // static_cast<uint16_t>(std::ceil(samples.getNumberOfSamples() * chunk));
    frames_ = Aquila::FramesCollection(in, /*samplesInFrame*/2048,
                                                               /*static_cast<unsigned int>(std::round(overlap * samplesInFrame))*/1638);
    std::cout << "samples per frame "<< frames_.getSamplesPerFrame();
    Aquila::Spectrogram spectrogram{frames_};
    std::cout << " w = " << w << " h = " << h << std::endl;
    std::cout << "frames count " << spectrogram.getFrameCount() <<  "samples count " << samples.getNumberOfSamples() << '\n';

    uint16_t freq = 0;
    float width_ratio = (spectrogram.getFrameCount()  * 1.0)/ w;
    float float_x = 0.0;
    size_t j = 0;
    size_t counter = 0;
    for (size_t x = 0; x < spectrogram.getFrameCount(); j++) {
        freq = 0;
        // output only half of the spectrogram, below Nyquist frequency
        for (std::size_t y = 1; y < h; ++y) {

            Aquila::ComplexType point = spectrogram.getPoint(x, freq);
            unsigned int color[] = {0, 0, 0};
            double value = point.real() * point.real() + point.imag() * point.imag();
            value = 0.5 * std::log10(value + 1);
            // std::cout << "value = " << value << std::endl;
            RGB rgbColor = gradient_.getColor(value);
            // std::cout << "x "<< x << std::endl;

            freq = static_cast<uint16_t> ((y * 1.)/h * 0.5 * samplesInFrame);
            data_[counter++] = rgbColor.r;
        }
        float_x += width_ratio;
        x = static_cast<size_t>(float_x);

    }

}

void Spectrogram::initColors() {
    for (uint16_t i = 256; i > 0; i -= 8) {
        gradient_.colors.push_back({i, i, i});
    }

    gradient_.colors.push_back({0, 0, 0});

}

void Spectrogram::saveImage(const char * filename) {

    cimg_library::CImg<unsigned char> simg{static_cast<unsigned  int>(200), static_cast<unsigned  int>(100), 1, 3, 0};
    unsigned char color[3];
    size_t x = 0, y = 0, counter = 0;
    for (int x = 0; x < 200; ++x) {
        for (int y = 0; y < 100; ++y) {

            color[0] = color[1] = color[2] = data_[counter++];

            simg.draw_point(x, y, 0, color);
        }
    }

    simg.save_jpeg(filename);
}

