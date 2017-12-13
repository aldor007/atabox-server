/*
 * functions.h
 *
 *  Created on: 8 cze 2014
 *      Author: aldor
 */

#ifndef ALDOR_FUNCTIONS_H_
#define ALDOR_FUNCTIONS_H_
#pragma once

#include <wave/processing/Processor.h>
#include <wave/analysis/SamplesAnalyzer.h>
#include <functions.h>
#include "wave/analysis/Property.h"
#include "aquila/transform/Spectrogram.h"

/*PROPERTY*/
#include "wave/analysis/AmplitudeProperty.h"
#include "wave/analysis/LengthProperty.h"
#include "wave/analysis/ZeroCrossingsProperty.h"
#include "wave/analysis/PercentageAboveProperty.h"
#include "wave/analysis/WhereIsAmplitudeProperty.h"
#include "wave/analysis/AverageValueProperty.h"
#include "wave/analysis/MfccProperty.h"

/*FILTER*/

#include "wave/processing/preprocessing/SilenceCuttingFilter.h"

#include "wave/processing/preprocessing/NormalizingFilter.h"

#include "wave/processing/postprocessing/HannWindowFilter.h"
#include "wave/processing/postprocessing/FastFourierTransformFilter.h"
void init_ProcessAndAnalize(SamplesAnalyzer &monstru);

void getColor(double level, unsigned char * color);
void drawSpectogram(Samples& samples, const char * file);

template <typename T>
std::tuple<double, double, double> calculateStatictic(std::vector<T> data) {
    size_t dataLen = data.size();
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double mean = sum / dataLen;

    std::vector<double> diff(dataLen);
    std::transform(data.begin(), data.end(), diff.begin(), [mean](double x) { return x - mean; });

    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double variance = sq_sum / dataLen;
    double stdev = std::sqrt(variance);

    return  std::make_tuple(mean, stdev, variance);
}

template <typename T>
void normalize(T &val, const size_t max) {
    size_t len = max - val.size();
    if (len > 200) {
        // LOG(warning) << "Normalize len bigger then treshold " << len;
    }

    for (size_t i = 0, len = max - val.size(); i < len; ++i) {
        val.push_back(0.0);
    }
}

template <typename T, typename C>
size_t normalizeArray(T &data, size_t max = 0, T &labels = nullptr ) {
    if (data.size() == 0) {
        return 0;
    }

    size_t min = std::numeric_limits<size_t>::max();
    size_t avg = 0;
    std::vector<size_t> sizes;
    sizes.reserve(data.size());

    if (max == 0) {
        for (C &val: data) {
            size_t size = val.size();
            if (size > max) {
                max = size;
            }

            if (size < min) {
                min = size;
            }

            avg += size;
            sizes.push_back(size);
        }

        std::tuple<double, double, double> stats = calculateStatictic(sizes);
        double stdev = std::get<1>(stats);
        std::vector<size_t>::iterator maxIt = std::max_element(sizes.begin(), sizes.end());
        max = *maxIt;
        avg /= data.size();

        LOG(info) << "Normalize min = " << min << " avg = " << avg << " max = " << max << '\n';
        LOG(info) << "Normalize stddev = " << std::get<1>(stats) << " var = " << std::get<2>(stats) << '\n';
        int counter = 0;
        while (max > (8 * stdev + avg)) {
            sizes.erase(maxIt);
            size_t c = maxIt - sizes.begin();
            data.erase(data.begin() + c);
            labels.erase(labels.begin() + c);
            maxIt = std::max_element(sizes.begin(), sizes.end());
            max = *maxIt;
            // std::cout << "Max in loop "<< max << " it " << maxIt - sizes.begin() << "size = " << sizes.size() << '\n';
        }

        LOG(info) << "Normalize min = " << min << " avg = " << avg << " max = " << max << '\n';
        LOG(info) << "Normalize stddev = " << std::get<1>(stats) << " var = " << std::get<2>(stats) << '\n';
    }


    for (C &val: data) {
        normalize<C>(val, max);
    }

    return max;
}

template< typename order_iterator, typename value_iterator >
void reorder( order_iterator order_begin, order_iterator order_end, value_iterator v )  {
    typedef typename std::iterator_traits< value_iterator >::value_type value_t;
    typedef typename std::iterator_traits< order_iterator >::value_type index_t;
    typedef typename std::iterator_traits< order_iterator >::difference_type diff_t;

    diff_t remaining = order_end - 1 - order_begin;
    for ( index_t s = index_t(), d; remaining > 0; ++ s ) {
        for ( d = order_begin[s]; d > s; d = order_begin[d] ) ;
        if ( d == s ) {
            -- remaining;
            value_t temp = v[s];
            while ( d = order_begin[d], d != s ) {
                std::swap( temp, v[d] );
                -- remaining;
            }
            v[s] = temp;
        }
    }
}



void save_2d_npy(std::string filename, std::vector<std::vector<double>> &data);
void save_1d_npy(std::string filename, std::vector<double> &data);
#endif /* FUNCTIONS_H_ */
