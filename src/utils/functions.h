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
		int step = 10;
		for (int i = 0; i < 100; i += step) {
			firstAnalizator->addProperty(new AmplitudeProperty(i, i + step));
			firstAnalizator->addProperty(new PercentageAboveProperty(0.01 * i));
			firstAnalizator->addProperty(new ZeroCrossingsProperty(i, i + step));
			firstAnalizator->addProperty(new AverageValueProperty(i, i + step));
		}
		firstAnalizator->addProperty(new LengthProperty());
		firstAnalizator->addProperty(new WhereIsAmplitudeProperty());

		monstru.add(std::make_pair(firstProcessor, firstAnalizator));


}

#endif /* FUNCTIONS_H_ */
