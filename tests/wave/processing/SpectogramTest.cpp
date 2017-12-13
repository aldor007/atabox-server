//
// Created by aldor on 28.05.16.
//


#include <wave/Samples.h>
#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "wave/processing/Spectrogram.h"


class SpectogramTest: public ::testing::Test {

};

TEST_F(SpectogramTest, testDraw) {

    WaveFile wave{"./tests/wave/waveFiles/prosze32bit.wav"};
    Samples sample{wave};
    Spectrogram spec{sample, 0.5, 0.5};
    spec.saveImage("./prosze-spec-bw.jpg");
}

