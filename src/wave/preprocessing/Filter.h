/*
 * Filter.h
 *
 *  Created on: 6 cze 2014
 *      Author: mj
 */

#ifndef FILTER_H_
#define FILTER_H_
#include "../Samples.h"
class Filter {
public:
	virtual void applyOn(Samples& samples) = 0;
	// TODO virtual Samples applyOn(Samples& samples) = 0;
	virtual ~Filter(){};
};

#endif /* FILTER_H_ */
