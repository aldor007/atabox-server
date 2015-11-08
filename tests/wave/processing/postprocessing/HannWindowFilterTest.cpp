#include <complex>
#include <cmath>

#include "wave/processing/postprocessing/HannWindowFilter.h"
#ifndef GTEST_H_
	#define GTEST_H_
	#include "gtest/gtest.h"
#endif

class HannWindowFilterTest: public ::testing::Test {
public:
	HannWindowFilter filter;

};

TEST_F(HannWindowFilterTest, exampleData) {
	//given
	Samples samples;
	double test[]  = { 0, 1};

	samples.setSamplesData(test, 2, 2);
	double result []= { 0,  0.5 * (1 - cos(M_PI)) };


	filter.applyOn(samples);
  ASSERT_EQ(samples.getSample(0), result[0]);
  ASSERT_EQ(samples.getSample(1), result[1]);

}

