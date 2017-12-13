//
// Created by aldor on 28.05.16.
//

#ifndef ATABOX_SERVER_SPECTOGRAM_H
#define ATABOX_SERVER_SPECTOGRAM_H


#include <shark/Unsupervised/RBM/GaussianBinaryRBM.h>
#include <aquila/transform/Spectrogram.h>


#include <wave/Samples.h>
#include <source/FramesCollection.h>

class Spectrogram {
public:
    Spectrogram(const Samples& sample, float chunk =0.0, float overlap = 0.0);
    Spectrogram(){}

    shark::RealVector getData() {
        return data_;
    }

    void saveImage(const char *file);

private:
    void initColors();
    struct RGB {
        uint16_t r,g,b;
    };

    struct ColorGradient {
        RGB getColor(double value) {
            // printf("value = %lf ", value);
            if (value >= max) {
                return colors.back();
            }

            size_t len = colors.size();
            float ratio = value / max;
            float width = 1. / static_cast<float>(len - 1);
            uint16_t i = 0;
            while (ratio > width) {
                ratio -= width;
                i++;
            }

            ratio *= len - 1;
            RGB first = colors[i];
            RGB second = colors[i + 1];

            RGB color;
            color.r = interpolate(first.r, second.r, ratio);
            color.g = interpolate(first.g, second.g, ratio);
            color.b = interpolate(first.b, second.b, ratio);

            return color;
        }

        inline uint16_t interpolate(uint16_t start, uint16_t finish, float ratio) {
            float val = (finish - start) * ratio + start * 1.;
            return val;
        }

        std::vector<RGB> colors;
        double max = 15;
    };

    Aquila::FramesCollection frames_;
    ColorGradient gradient_;
    shark::RealVector data_;
};

#endif //ATABOX_SERVER_SPECTOGRAM_H
