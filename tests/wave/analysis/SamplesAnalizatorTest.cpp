#include "wave/Samples.h"
#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "wave/analysis/SamplesAnalizator.h"
#include "cpprest/json.h"
#include "FirstSampleValueTestingProperty.h"
namespace webjs = web::json;
using ::testing::Return;


class SamplesAnalizatorTest: public ::testing::Test {

};


TEST_F(SamplesAnalizatorTest, changesSamplesWhenFiltersAreAdded) {

	//given
	Samples samples;
	cx * values = new cx[4];
	values[0] = 0.128;
	values[1] = -0.5;
	values[2] = 0.16;
	values[3] =  0.130;
	samples.setSampleListData(4, values);

	FirstSampleValueTestingProperty property;

	SamplesAnalizator analizator;
	analizator.addProperty(property);

	//when
	webjs::value result = analizator.getPropertiesSummary(samples);

	//then
	string name("firstSampleValue");
	double value = result[name].as_double();
	ASSERT_DOUBLE_EQ(value, 0.128);
}










