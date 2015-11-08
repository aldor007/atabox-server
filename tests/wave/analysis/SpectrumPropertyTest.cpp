
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "wave/Samples.h"
#include "../SamplesMock.h"
#include "wave/analysis/SpectrumProperty.h"

using ::testing::Return;
using ::testing::ReturnRef;

class SpectrumPropertyTest: public ::testing::Test {
public:
	/*std::unique_ptr<double[]> samplesValue;

	SpectrumPropertyTest(): samplesValue(new double[6])  {
	samplesValue[0]	=  double(1, 0);
	samplesValue[1] = double(0, 0);
	samplesValue[2] = double(0, 0);
	samplesValue[3] = double(0, 0);
	samplesValue[4] = double(5, 0);
	samplesValue[5] = double(5, 0);
	}*/

};

TEST_F(SpectrumPropertyTest,  testCalulate) {
	//given
	Samples samples;

	double * samplesValue = new double[6];
	samplesValue[0]	= 10;
	samplesValue[1] = 0;
	samplesValue[2] = 0;
	samplesValue[3] = 0;
	samplesValue[4] = 0;
	samplesValue[5] = 100;
	samples.setSamplesData(samplesValue, 6, 6);

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
