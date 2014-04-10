/*
 * PropertiesComparator.h
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#ifndef PROPERTIESCOMPARATOR_H_
#define PROPERTIESCOMPARATOR_H_
#include "wave/WaveProperties.h"
class PropertiesComparator {
public:
	PropertiesComparator();
	~PropertiesComparator();
	double getSimilarityRatio(WaveProperties firstFile,
			WaveProperties secondFile);
};

#endif /* PROPERTIESCOMPARATOR_H_ */
