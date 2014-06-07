/*
 * SilenceCuttingFilter.h
 *
 *  Created on: 6 cze 2014
 *      Author: mj
 */

#ifndef SILENCECUTTINGFILTER_H_
#define SILENCECUTTINGFILTER_H_
#include "Filter.h"


class SilenceCuttingFilter: Filter {

void applyOn(Samples &samples);
	~SilenceCuttingFilter();
};

#endif /* SILENCECUTTINGFILTER_H_ */
