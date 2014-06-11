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

public:
	SpectrumProperty(double weight = 1.0) : Property(weight)  {

	}
	virtual double getValue(const Samples& samples) {
		if (samples.getNumberOfSamples() == 0)
			return 0;
      uint32_t len = samples.getNumberOfSamples()/2.0;
	  std::valarray<double>    magnitude = std::valarray<double>(len);

          for (uint32_t i = 0; i <len; i++)	{
              magnitude[i] = std::abs(samples[i]);

                }
		std::log10(magnitude);
		double value = (magnitude.max() - magnitude.min())/magnitude.sum();
		if (value != value)
			return 1;
		return value;
	}


	virtual std::string getName() {
		return "spectrum";
	}
};

#endif /* SPECTRUMPROPERTY_H_ */
