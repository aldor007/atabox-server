//
// Created by Marcin Kaciuba on 03.05.2016.
//

#include <wave/analysis/LpccProperty.h>
#include <cnpy.h>
#include "utils/functions.h"
#include "utils/atabox_log.h"

void init_ProcessAndAnalize(SamplesAnalyzer
                            &monstru) {


    Processor * firstProcessor = new Processor();
        firstProcessor->addToFilterChain(new NormalizingFilter(1.0));
        firstProcessor->addToFilterChain(new SilenceCuttingFilter(0.2));
        SamplesAnalyzer * firstAnalizator = new SamplesAnalyzer();
        firstAnalizator->addArrayProperty(new MfccProperty());
        firstAnalizator->addArrayProperty(new LpccProperty());
        int step = 10;
        for (int i = 0; i < 100; i += step) {
            firstAnalizator->addProperty(new AmplitudeProperty(i, i + step));
            firstAnalizator->addProperty(new PercentageAboveProperty(0.01 * i));
            firstAnalizator->addProperty(new ZeroCrossingsProperty(i, i + step));
            firstAnalizator->addProperty(new AverageValueProperty(i, i + step));
        }
        firstAnalizator->addProperty(new LengthProperty());
        firstAnalizator->addProperty(new WhereIsAmplitudeProperty());
//        monstru.add(std::make_pair(firstProcessor, firstAnalizator));
}

void getColor(double level, unsigned char * color) {

   level *= 0.6625;
   double c = 0.0;
   if (level >= 0 && level < 0.15) {
          c = (0.15 - level) / (0.15 + 0.075);
      } else if (level >= 0.15 && level < 0.275) {
          c = (level - 0.15) / (0.275 - 0.15);
      } else if (level >= 0.275 && level < 0.325) {
          c = (0.325 - level) / (0.325 - 0.275);
      } else if (level >= 0.325 && level < 0.5) {
          c = (level - 0.325) / (0.5 - 0.325);
      } else  {
          c = (0.6625 - level) / (0.6625 - 0.5f);
       }

   // Intensity correction.
   double cf = 1.0;
   if (level >= 0.0 && level < 0.1) {
           cf = level / 0.1;
       }
   cf *= 255.0;

   // Pack RGB values into a 32-bit uint.
//   uint32_t rr = (uint32_t) (r * cf + 0.5);
//   uint32_t gg = (uint32_t) (g * cf + 0.5);
//   uint32_t bb = (uint32_t) (b * cf + 0.5)
    color[0] = (unsigned char) (1./c * cf + 0.5);
    color[1] = (unsigned char) (1./c * cf + 0.5);
    color[2] = (unsigned char) (1./c * cf + 0.5);
}

void drawSpectogram(Samples& samples, const char * file) {

    uint16_t samplesInFrame = static_cast<uint16_t>(std::ceil(samples.getNumberOfSamples() / MfccProperty::MAX_FRAME));
    Aquila::FramesCollection frames = Aquila::FramesCollection(samples, samplesInFrame,
                                                               static_cast<unsigned  int>(std::round(0.2 * samplesInFrame)));
    std::cout << "samples per frame "<< frames.getSamplesPerFrame();
    Aquila::Spectrogram spectrogram{frames};
    size_t w = 800;
    size_t h =  600;
    std::cout << " w = " << w << " h = " << h << std::endl;
    cimg_library::CImg<unsigned char> simg{static_cast<unsigned  int>(800), static_cast<unsigned  int>(600), 1, 2, 0};
    for (std::size_t x = 0; x < spectrogram.getFrameCount(); ++x) {

        // output only half of the spectrogram, below Nyquist frequency
        for (std::size_t y = h/2; y < h ; ++y) {

            Aquila::ComplexType point = spectrogram.getPoint(x, y);
            unsigned char color[] = {0, 0, 0};
            double value = point.real() * point.real() + point.imag() * point.imag();
            value = 0.5 * std::log10(value + 1);
            std::cout << "value = " << value << std::endl;
            getColor(value, color);
//            color[0] = (unsigned char) (125 + sDb);
//            color[1] = (unsigned char) (125 + sDb);
//            color[2] = (unsigned char) (125 + sDb);
            simg.draw_point(x, y, 0, color);
        }
    }

    simg.save_jpeg(file);
}


void save_2d_npy(std::string filename, std::vector<std::vector<double>> &data) {
    unsigned int shape[2];
    shape[0] = data.size();
    shape[1] = data.begin()->size();

    std::vector<double> converted;

    std::cout << filename << " " << shape[0] << " "  << shape[1] << '\n';

    for (auto& t: data) {
        converted.insert(converted.end(), t.begin(), t.end());
    }

    cnpy::npy_save(filename, converted.data(), shape, 2);
}

void save_1d_npy(std::string filename, std::vector<double> &data) {
    unsigned int shape[2];
    shape[0] = data.size();
    shape[1] = 1;

    cnpy::npy_save(filename, data.data(), shape, 1);
}
