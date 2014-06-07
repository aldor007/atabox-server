/*
 * NormalizingFilter.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef NORMALIZINGFILTER_H_
#define NORMALIZINGFILTER_H_
#include "Filter.h"

class NormalizingFilter : Filter {
public:
	NormalizingFilter();
	void applyOn(Samples& samples);
};

#endif /* NORMALIZINGFILTER_H_ */
