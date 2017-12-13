//
// Created by aldor on 08.11.15.
//

#ifndef ATABOX_SERVER_GLOBAL_H
#define ATABOX_SERVER_GLOBAL_H

#include "aquila/global.h"

// turn of U in cpprest
#define _TURN_OFF_PLATFORM_STRING 1

#define cimg_display 0
#define cimg_use_jpeg 1
#define cimg_use_png 1
#undef U

#include "CImg.h"

namespace atabox {
    /**
    * Library version in an easily comparable format.
    */
    const long VERSION_NUMBER = 0x100000;

    /**
     * Library version as a string.
     */
    const char* const VERSION_STRING = "1.0.0-dev";

    /**
     * Sample value type.
     */
    typedef Aquila::SampleType SampleType;

    /**
     * Sample frequency type.
     */
    typedef Aquila::FrequencyType FrequencyType;

    /**
     * Our standard complex number type, using double precision.
     */
    typedef Aquila::ComplexType ComplexType;

    /**
     * Spectrum type - a vector of complex values.
     */
    typedef Aquila::SpectrumType SpectrumType;

}
#endif //ATABOX_SERVER_GLOBAL_H
