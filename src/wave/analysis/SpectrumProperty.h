/*
 * SpectrumProperty.h
 *
 *  Created on: 8 cze 2014
 *      Author: aldor
 */

#ifndef SPECTRUMPROPERTY_H_
#define SPECTRUMPROPERTY_H_

#include <cmath>
#include <valarray>
#include "utils/atabox_log.h"

#include "wave/Samples.h"
#include "wave/analysis/Property.h"

class SpectrumProperty: public Property {
private:
	  std::valarray<double> m_magnitude;
	  void callculateMagnitude(const Samples& samples) {

           double len = samples.getNumberOfSamples()/2.0;
          if (m_magnitude.size() < len)
               m_magnitude = std::valarray<double>(len);

          for (uint32_t i = 0; i <len; i++)	{
              m_magnitude[i] = std::abs(samples[i]);

                }

	  }

public:
	SpectrumProperty(double weight = 1.0) : Property(weight), m_magnitude(1) {

	}
	virtual double getValue(const Samples& samples) {
		if (samples.getNumberOfSamples() == 0)
			return 0;
		callculateMagnitude(samples);
		std::log10(m_magnitude);
		double value = (m_magnitude.max() - m_magnitude.min())/m_magnitude.sum();
		if (value != value)
			return 1;
		return value;
	}


	virtual std::string getName() {
		return "spectrum";
	}
};

#endif /* SPECTRUMPROPERTY_H_ */
