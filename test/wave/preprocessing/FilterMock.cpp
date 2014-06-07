/*
 * FilterMock.cpp
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

/*
 * FilterMock.h
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#ifndef FILTERMOCK_H_
#define FILTERMOCK_H_
#include "wave/preprocessing/Filter.h"
class FilterMock: Filter {

	void applyOn(Samples& samples) {
		for (int i = 0; i < samples.getNumberOfSamples(); ++i) {
			samples.setSample(i, 0.0);
		}
	}

};

#endif /* FILTERMOCK_H_ */
