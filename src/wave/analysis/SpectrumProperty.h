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
#include "wave/Samples.h"
#include "wave/analysis/Property.h"

class SpectrumProperty: public Property {
private:
	  std::valarray<double> m_magnitude;
	  void callculateMagnitude(Samples& samples) {

           uint32_t len = samples.getNumberOfSamples();
          if (m_magnitude.size() != len)
               m_magnitude = std::valarray<double>(len);

          for (uint32_t i = 0; i <len; i++)	{
              m_magnitude[i] = std::abs(samples[i]);

                }

	  }

public:
	virtual double getValue(Samples& samples) {
		callculateMagnitude(samples);
		std::log10(m_magnitude);
		double value = (m_magnitude.max() - m_magnitude.min()) / m_magnitude.sum();

	}


	virtual std::string getName() {
		return "spectrum";
	}
};

#endif /* SPECTRUMPROPERTY_H_ */
