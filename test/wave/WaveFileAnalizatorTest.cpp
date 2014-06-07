#include "wave/analysis/SamplesAnalizator.h"
#include "wave/Samples.h"
#include "../test/wave/SamplesMock.h"
#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;

class SamplesAnalizatorTest: public ::testing::Test {

};


TEST_F(SamplesAnalizatorTest, countsPercentageAboveCorrectly) {
	//given
	SamplesMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(-0.11));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(0.7));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.2));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(1));
	ON_CALL(samples, getSample(4)).WillByDefault(Return(-1));

	//when
	SamplesAnalizator analizator;
	double percentageAbove = analizator.percentageAbove(samples, 0.5);

	//then
	ASSERT_DOUBLE_EQ(percentageAbove, 3.0/5.0);
}

TEST_F(SamplesAnalizatorTest, countsPercentageBelowCorrectly) {
	//given
	SamplesMock samples;
	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(samples, getSample(0)).WillByDefault(Return(-0.11));
	ON_CALL(samples, getSample(1)).WillByDefault(Return(0.7));
	ON_CALL(samples, getSample(2)).WillByDefault(Return(0.2));
	ON_CALL(samples, getSample(3)).WillByDefault(Return(1));
	ON_CALL(samples, getSample(4)).WillByDefault(Return(-1));

	//when
	SamplesAnalizator analizator;
	double percentageBelow = analizator.percetnageBelow(samples, 0.5);

	//then
	ASSERT_DOUBLE_EQ(percentageBelow, 2.0/5.0);
}






