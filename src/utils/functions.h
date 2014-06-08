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


	Processor firstProcessor;
	firstProcessor.addToFilterChain(new NormalizingFilter(1.0));
	firstProcessor.addToFilterChain(new SilenceCuttingFilter(0.02));
	SamplesAnalizator  firstAnalizator;// = new SamplesAnalizator();
	firstAnalizator.addProperty(new AmplitudeProperty());
	firstAnalizator.addProperty(new LengthProperty());
	firstAnalizator.addProperty(new ZeroCrossingsProperty());
	firstAnalizator.addProperty(new PercentageAboveProperty(0.5));
	firstAnalizator.addProperty(new WhereIsAmplitudeProperty());
	firstAnalizator.addProperty(new AverageValueProperty());

	monstru.add(std::make_pair(firstProcessor, firstAnalizator ));
	Processor secondProssor;
	secondProssor.addToFilterChain(new HannWindowFilter());
	secondProssor.addToFilterChain(new FastFourierTransformFilter());
	SamplesAnalizator secondAnalizator;
	secondAnalizator.addProperty(new SpectrumProperty());
	monstru.add(std::make_pair(secondProssor, secondAnalizator));



}

#endif /* FUNCTIONS_H_ */
