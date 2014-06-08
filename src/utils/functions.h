/*
 * functions.h
 *
 *  Created on: 8 cze 2014
 *      Author: aldor
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "wave/analysis/Property.h"


/*PROPERTY*/
#include "wave/analysis/AmplitudeProperty.h"
#include "wave/analysis/LengthProperty.h"
#include "wave/analysis/ZeroCrossingsProperty.h"


/*FILTER*/
#include "wave/preprocessing/SilenceCuttingFilter.h"



void inti_SampleAnalizator(SamplesAnalizator &analizator) {

	analizator.addProperty(new AmplitudeProperty());
	analizator.addProperty(new LengthProperty());
	analizator.addProperty(new ZeroCrossingsProperty());


}

void init_Preprocessor(Preprocessor &preprocessor) {

		preprocessor.addToFilterChain(new SilenceCuttingFilter(0.02));
}

#endif /* FUNCTIONS_H_ */
