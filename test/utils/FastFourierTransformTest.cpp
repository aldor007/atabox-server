
#include "recognition/PropertiesComparator.h"

#include "gtest/gtest.h"
#include "utils/FastFourierTransform.h"
#include "wave/WaveFile.h"
#include <complex>

class FastFourierTransformTest: public ::testing::Test {

};

TEST_F(FastFourierTransformTest, exampleData) {
	//given
	typedef std::complex<double> cx;
	cx indata[] = { cx(0,0), cx(1,1), cx(3,3), cx(4,4),
	cx(4, 4), cx(3, 3), cx(1,1), cx(0,0) };
	cx outdata[8];
	FastFourierTransform(indata, outdata, 3);
	ASSERT_EQ(outdata[0], cx(16, 16));
}

TEST_F(FastFourierTransformTest, waveData) {
	//given
	typedef std::complex<double> cx;
	WaveFile waveFile("test/wave/dziekuje32bit.wav");
	cx * outdata = new cx[waveFile.getNumberOfSamples()];
	FastFourierTransform(waveFile, outdata, 3);
	std::cout<<"tst "<<waveFile[0]<<std::endl;
	ASSERT_EQ(outdata[0], cx(16, 16));
}
