#include <wave/analysis/SamplesAnalyzer.h>
#include "wave/Samples.h"
#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cpprest/json.h"
#include "FirstSampleValueTestingProperty.h"
namespace webjs = web::json;
using ::testing::Return;


class SamplesAnalizatorTest: public ::testing::Test {

};


TEST_F(SamplesAnalizatorTest, changesSamplesWhenFiltersAreAdded) {

	//given
	Samples samples;
	double * values = new double[4];
	values[0] = 0.128;
	values[1] = -0.5;
	values[2] = 0.16;
	values[3] =  0.130;
	samples.setSamplesData(values, 4, 4);

	FirstSampleValueTestingProperty property;

	SamplesAnalyzer analizator;
	analizator.addProperty(property);

	//when
	webjs::value result = analizator.getPropertiesSummary(samples);

	//then
	std::string name("firstSampleValue");
	double value = result[name].as_double();
	ASSERT_DOUBLE_EQ(value, 0.128);
}










