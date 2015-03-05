/*
 * ZeroCrossingsPropertyPropertyTest.cpp
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#include <gtest/internal/gtest-internal.h>
#include <utils/jsonextend.h>
#include <wave/analysis/SamplesAnalizator.h>
#include <wave/processing/Processor.h>
#include <wave/Samples.h>
#include <wave/WaveFile.h>
#include <iostream>
#include <string>
#include <utility>

#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"

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

#include <recognition/PropertiesComparator.h>

using ::testing::Return;

// class VimWaveRunner: public ::testing::Test {
//
// };
//
// void init_ProcessAndAnalizeTest(ProcessAndAnalyze &monstru) {
//
// 	Processor * firstProcessor = new Processor();
// 	firstProcessor->addToFilterChain(new NormalizingFilter(1.0));
// 	firstProcessor->addToFilterChain(new SilenceCuttingFilter(0.2));
// 	SamplesAnalizator * firstAnalizator = new SamplesAnalizator();
// 	int step = 10;
// 	for (int i = 0; i < 100; i += step) {
// 		firstAnalizator->addProperty(new AmplitudeProperty(i, i + step));
// 		firstAnalizator->addProperty(new PercentageAboveProperty(0.01 * i));
// 		firstAnalizator->addProperty(new ZeroCrossingsProperty(i, i + step));
// 		firstAnalizator->addProperty(new AverageValueProperty(i, i + step));
// 	}
// 	firstAnalizator->addProperty(new LengthProperty());
// 	firstAnalizator->addProperty(new WhereIsAmplitudeProperty());
//
// 	monstru.add(std::make_pair(firstProcessor, firstAnalizator));
//
//
// //	Processor * secondProssor = new Processor();
// //	secondProssor->addToFilterChain(new HannWindowFilter());
// //	secondProssor->addToFilterChain(new FastFourierTransformFilter());
// //	SamplesAnalizator * secondAnalizator = new SamplesAnalizator();
// //	secondAnalizator->addProperty(new SpectrumProperty(0.85));
// //	monstru.add(std::make_pair(secondProssor, secondAnalizator));
//
// }
//
// double getDistanceBetweenFiles(const char* fileName1, const char* fileName2) {
// 	//given
// 	WaveFile vimWaveFile(fileName1);
// 	Samples vimSamples(vimWaveFile);
// 	WaveFile ciszejWaveFile(fileName2);
// 	Samples ciszejSamples(ciszejWaveFile);
// 	ProcessAndAnalyze g_processAndAnlyze;
// 	init_ProcessAndAnalizeTest(g_processAndAnlyze);
// 	//when
// 	jsonextend vimSummary = g_processAndAnlyze.getSummary(vimSamples);
// 	jsonextend ciszejSummary = g_processAndAnlyze.getSummary(ciszejSamples);
// 	std::cout << vimSummary.to_string();
// 	std::cout << std::endl;
// 	std::cout << ciszejSummary.to_string();
// 	std::cout << std::endl;
// 	//then
// 	PropertiesComparator comparator;
// 	double distance = comparator.getDistance(vimSummary, ciszejSummary);
// 	return distance;
// }
//
// TEST_F(VimWaveRunner, twoVimRecordsAreCloserToEachOtherThanWithCiszejWave) {
//
// 	//given
// 	double distance = getDistanceBetweenFiles(
// 			"tests/wave/waveFiles/vim32bit_1.wav",
// 			"tests/wave/waveFiles/ciszej32bit_1.wav");
// 	double distanceBetweenTheSameFiles = getDistanceBetweenFiles(
// 			"tests/wave/waveFiles/vim32bit_1.wav",
// 			"tests/wave/waveFiles/vim32bit_2.wav");
// 	std::cout << distance << std::endl;
// 	std::cout << distanceBetweenTheSameFiles << std::endl;
//
// 	ASSERT_LT(distanceBetweenTheSameFiles, distance);
// }
//
// TEST_F(VimWaveRunner, scenario2) {
//
// 	//given
// 	double distance = getDistanceBetweenFiles(
// 			"tests/wave/waveFiles/vim32bit_1.wav",
// 			"tests/wave/waveFiles/ciszej32bit_1.wav");
// 	double distanceBetweenTheSameFiles = getDistanceBetweenFiles(
// 			"tests/wave/waveFiles/vim32bit_1.wav",
// 			"tests/wave/waveFiles/vim32bit_3.wav");
// 	std::cout << distance << std::endl;
// 	std::cout << distanceBetweenTheSameFiles << std::endl;
//
// 	ASSERT_LT(distanceBetweenTheSameFiles, distance);
// }
//
// TEST_F(VimWaveRunner, scenario3) {
//
// 	//given
// 	double distance = getDistanceBetweenFiles(
// 			"tests/wave/waveFiles/vim32bit_1.wav",
// 			"tests/wave/waveFiles/przegladarka32bit_1.wav");
// 	double distanceBetweenTheSameFiles = getDistanceBetweenFiles(
// 			"tests/wave/waveFiles/vim32bit_1.wav",
// 			"tests/wave/waveFiles/vim32bit_3.wav");
// 	std::cout << distance << std::endl;
// 	std::cout << distanceBetweenTheSameFiles << std::endl;
//
// 	ASSERT_LT(distanceBetweenTheSameFiles, distance);
// }
//
// TEST_F(VimWaveRunner, scenario4) {
//
// 	//given
// 	double distanceBetweenTheSameFiles = getDistanceBetweenFiles(
// 			"tests/wave/waveFiles/dziekuje32bit.wav",
// 			"tests/wave/waveFiles/dziekuje32bitSmallNoise.wav");
// 	double distance = getDistanceBetweenFiles(
// 			"tests/wave/waveFiles/dziekuje32bit.wav",
// 			"tests/wave/waveFiles/dzienDobry32bit.wav");
// 	std::cout << distance << std::endl;
// 	std::cout << distanceBetweenTheSameFiles << std::endl;
//
// 	ASSERT_LT(distanceBetweenTheSameFiles, distance);
// }
//
// TEST_F(VimWaveRunner, scenario5) {
//
// 	//given
// 	double distanceBetweenTheSameFiles = getDistanceBetweenFiles(
// 			"tests/wave/waveFiles/dziekuje32bit.wav",
// 			"tests/wave/waveFiles/dziekuje32bitMediumNoise.wav");
// 	double distance = getDistanceBetweenFiles(
// 			"tests/wave/waveFiles/dziekuje32bit.wav",
// 			"tests/wave/waveFiles/dzienDobry32bit.wav");
// 	std::cout << distance << std::endl;
// 	std::cout << distanceBetweenTheSameFiles << std::endl;
//
// 	ASSERT_LT(distanceBetweenTheSameFiles, distance);
// }
//
