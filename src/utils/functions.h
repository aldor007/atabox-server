/*
 * functions.h
 *
 *  Created on: 8 cze 2014
 *      Author: aldor
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "wave/analysis/Property.h"

#include "recognition/ProcessAndAnalyze.h"


/*PROPERTY*/
#include "wave/analysis/AmplitudeProperty.h"
#include "wave/analysis/LengthProperty.h"
#include "wave/analysis/ZeroCrossingsProperty.h"
#include "wave/analysis/PercentageAboveProperty.h"
#include "wave/analysis/WhereIsAmplitudeProperty.h"
#include "wave/analysis/AverageValueProperty.h"

#include "wave/analysis/SpectrumProperty.h"

/*FILTER*/

#include "wave/processing/preprocessing/SilenceCuttingFilter.h"
#include "wave/processing/preprocessing/NormalizingFilter.h"

#include "wave/processing/postprocessing/HannWindowFilter.h"
#include "wave/processing/postprocessing/FastFourierTransformFilter.h"





void init_ProcessAndAnalize(ProcessAndAnalyze &monstru) {


	Processor * firstProcessor = new Processor();
	firstProcessor->addToFilterChain(new NormalizingFilter(1.0));
	firstProcessor->addToFilterChain(new SilenceCuttingFilter(0.2));
	SamplesAnalizator * firstAnalizator = new SamplesAnalizator();
	firstAnalizator->addProperty(new AmplitudeProperty(0, 100, 2.2));
	firstAnalizator->addProperty(new LengthProperty(1.7));
	firstAnalizator->addProperty(new ZeroCrossingsProperty(0, 100, 1.5));
	firstAnalizator->addProperty(new ZeroCrossingsProperty(50, 100, 0.5));
	firstAnalizator->addProperty(new PercentageAboveProperty(0.5, 3.0));
	firstAnalizator->addProperty(new WhereIsAmplitudeProperty(0.75));
	firstAnalizator->addProperty(new AverageValueProperty(0, 80, 0.2));

	monstru.add(std::make_pair(firstProcessor, firstAnalizator ));
	Processor * secondProssor = new Processor();
	secondProssor->addToFilterChain(new HannWindowFilter());
	secondProssor->addToFilterChain(new FastFourierTransformFilter());
	SamplesAnalizator * secondAnalizator = new SamplesAnalizator();
	secondAnalizator->addProperty(new SpectrumProperty(0.85));
	monstru.add(std::make_pair(secondProssor, secondAnalizator));



}

#endif /* FUNCTIONS_H_ */
