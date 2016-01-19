
#include "wave/Samples.h"
#include "wave/analysis/Property.h"
#include "wave/processing/Filter.h"
#include "wave/processing/Processor.h"
#include "recognition/FeatureExtractor.h"


#include "cpprest/json.h"
#undef U
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using ::testing::Return;
using ::testing::_;



class ProcessorMock: public Processor {
public:
    ProcessorMock() {}
	virtual ~ProcessorMock(){}
	MOCK_METHOD1(addToFilterChain, void (Filter*));
	MOCK_METHOD1(addToFilterChain, void (Filter&));
	MOCK_METHOD1(applyFilterChainOn, void (Samples&));
};

class SamplesAnalizatorMock: public SamplesAnalyzer {
public:
	SamplesAnalizatorMock() {}
	virtual ~SamplesAnalizatorMock() {}
	MOCK_METHOD1(addProperty, void (Property*));
	MOCK_METHOD1(addProperty, void (Property&));
	MOCK_METHOD1(getPropertiesSummary, jsonextend (Samples&));
};


class ProcessAndAnalyzeTest: public ::testing::Test {

};

TEST_F(ProcessAndAnalyzeTest, testcall) {

	//given
     Samples samples;
	ProcessorMock * pre = new ProcessorMock();
	SamplesAnalizatorMock * analizator = new SamplesAnalizatorMock();

    jsonextend empty;
    empty["a"] = web::json::value::number(1);

   ON_CALL(*analizator, getPropertiesSummary(_)).WillByDefault(Return(empty));
	EXPECT_CALL(*pre, applyFilterChainOn(_)).Times(1);
	EXPECT_CALL(*analizator, getPropertiesSummary(_)).Times(1);

	FeatureExtractor monstru;
	monstru.add(std::make_pair(pre, analizator));
	jsonextend result = monstru.getSummary(samples);

	ASSERT_TRUE(result == empty);
}
