/*
 * SilenceCuttingFilterTest.cpp
 *
 *  Created on: 6 cze 2014
 *      Author: mj
 */

/*
 * PreprocessorTest.cpp
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#include <wave/Samples.h>
#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <wave/processing/preprocessing/NormalizingFilter.h>

using ::testing::Return;

class NormalizingFilterTest: public ::testing::Test {

};

TEST_F(NormalizingFilterTest, simpleExample) {

	//given
	Samples samples;
	double * values = new double[2];
	values[0] = 0.0128;
	values[1] = -0.5;

	samples.setSamplesData(values, 2, 2);
	NormalizingFilter filter;

	//when
	filter.applyOn(samples);
	delete[] values;

	//then
	ASSERT_DOUBLE_EQ(samples.getSample(0), 0.0256);
	ASSERT_DOUBLE_EQ(samples.getSample(1), -1.0);

}

TEST_F(NormalizingFilterTest, simpleExampleWithParameterLevel) {

	//given
	Samples samples;
	double * values = new double[2];
	values[0] = -0.1;
	values[1] = 0.2;

	samples.setSamplesData(values, 2, 2);
	NormalizingFilter filter(0.8);

	//when
	filter.applyOn(samples);
	delete[] values;
	

	//then
	ASSERT_DOUBLE_EQ(samples.getSample(0), -0.4);
	ASSERT_DOUBLE_EQ(samples.getSample(1), 0.8);

}
