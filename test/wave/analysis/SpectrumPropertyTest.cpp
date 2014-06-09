
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "wave/Samples.h"
#include "../SamplesMock.h"
#include "wave/analysis/SpectrumProperty.h"

using ::testing::Return;
using ::testing::ReturnRef;

class SpectrumPropertyTest: public ::testing::Test {
public:
	/*std::unique_ptr<cx[]> samplesValue;

	SpectrumPropertyTest(): samplesValue(new cx[6])  {
	samplesValue[0]	=  cx(1, 0);
	samplesValue[1] = cx(0, 0);
	samplesValue[2] = cx(0, 0);
	samplesValue[3] = cx(0, 0);
	samplesValue[4] = cx(5, 0);
	samplesValue[5] = cx(5, 0);
	}*/

};

TEST_F(SpectrumPropertyTest,  testCalulate) {
	//given
	SamplesMock samples;

	std::valarray<cx>  samplesValue(6);
	samplesValue[0]	=  cx(10, 0);
	samplesValue[1] = cx(0, 0);
	samplesValue[2] = cx(0, 0);
	samplesValue[3] = cx(0, 0);
	samplesValue[4] = cx(0, 0);
	samplesValue[5] = cx(100, 0);

	ON_CALL(samples, getNumberOfSamples()).WillByDefault(Return(5));
	ON_CALL(samples, getSampleCx(0)).WillByDefault(ReturnRef(samplesValue[0]));
	ON_CALL(samples, getSampleCx(1)).WillByDefault(ReturnRef(samplesValue[1]));
	ON_CALL(samples, getSampleCx(2)).WillByDefault(ReturnRef(samplesValue[2]));
	ON_CALL(samples, getSampleCx(3)).WillByDefault(ReturnRef(samplesValue[3]));
	ON_CALL(samples, getSampleCx(4)).WillByDefault(ReturnRef(samplesValue[4]));

	SpectrumProperty property;
	//when
	double result = property.getValue(samples);



	//then
	ASSERT_DOUBLE_EQ(result, 1.);
}

TEST_F(SpectrumPropertyTest, returnsCorrectName) {
	//given
	SpectrumProperty property;

	//when
	string name = property.getName();

	//then
	ASSERT_STRCASEEQ("spectrum", name.c_str());
}
