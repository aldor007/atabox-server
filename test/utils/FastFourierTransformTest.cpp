
#include "utils/FastFourierTransform.h"
#include "wave/WaveFile.h"
#include <complex>
#include <cmath>

#ifndef GTEST_H_
	#define GTEST_H_
	#include "gtest/gtest.h"
#endif

class FastFourierTransformTest: public ::testing::Test {

};

TEST_F(FastFourierTransformTest, exampleDataStacv) {
	//given
	typedef std::complex<double> cx;
	cx input[] =  { cx(0,0), cx(1,1), cx(3,3), cx(4,4),
			cx(4, 4), cx(3, 3), cx(1,1), cx(0,0) };
	 input[0] = 0.0;
	    input[1] = 162.6345596729059;
	    input[2] = 230.0;
	    input[3] = 162.63455967290594;
	    input[4] = 2.8166876380389125E-14;
	    input[5] = -162.6345596729059;
	    input[6] = -230.0;
	    input[7] = -162.63455967290597;
	cx *outdata = FastFourierTransform(input, 8);
  ASSERT_EQ(std::abs(outdata[1]), 920);
  ASSERT_EQ(std::abs(outdata[0]),  2.5483305001488234E-16);

}
TEST_F(FastFourierTransformTest, exampleDataBlog) {
	//given
	typedef std::complex<double> cx;
	cx indata[] =  { cx(0,0), cx(1,1), cx(3,3), cx(4,4),
			cx(4, 4), cx(3, 3), cx(1,1), cx(0,0) };
	cx *outdata  = FastFourierTransform(indata, 8);
	ASSERT_EQ(outdata[0], cx(16, 16));
  ASSERT_EQ(outdata[2], cx(0,0));


}
/*
TEST_F(FastFourierTransformTest, exampleData) {
	//given
	typedef std::complex<double> cx;
	cx indata[] = { cx(0,0), cx(1,0), cx(3,0), cx(4,0),
	cx(5, 0), cx(6, 0), cx(7,0)};
	cx outdata[8];
	FastFourierTransform(indata, outdata, 8);
	ASSERT_EQ(outdata[0], cx(26, 0));
   ASSERT_EQ(outdata[2], cx(-4, 4));


}*/

TEST_F(FastFourierTransformTest, TheSameWaveData) {
	//given
	typedef std::complex<double> cx;
	WaveFile waveFile("test/wave/waveFiles/dziekuje32bit.wav");
	//std::vector<cx> outdata;
	std::complex<double> * outdata = FastFourierTransform(waveFile, waveFile.getNumberOfSamples());

	WaveFile waveFile2("test/wave/waveFiles/dziekuje32bit.wav");
	cx *  outdata2 = FastFourierTransform(waveFile2, waveFile2.getNumberOfSamples());
	ASSERT_EQ(outdata[0], outdata2[0]);

}
/*
TEST_F(FastFourierTransformTest, TheSameWaveDataDiffrenBits) {
	//given
	typedef std::complex<double> cx;
	WaveFile waveFile("test/wave/waveFiles/dziekuje32bit.wav");
	//std::vector<cx> outdata;
	std::complex<double> * outdata = FastFourierTransform(waveFile, waveFile.getNumberOfSamples());

	WaveFile waveFile2("test/wave/waveFiles/dziekuje8bit.wav");
	cx *  outdata2 = FastFourierTransform(waveFile2, waveFile2.getNumberOfSamples());
	ASSERT_EQ(outdata[0], outdata2[0]);

}*/
TEST_F(FastFourierTransformTest, DiffrentWaveData) {
	//given
	typedef std::complex<double> cx;
	WaveFile waveFile("test/wave/waveFiles/dziekuje32bit.wav");
	//std::vector<cx> outdata;
	std::complex<double> * outdata = FastFourierTransform(waveFile, waveFile.getNumberOfSamples());

	WaveFile waveFile2("test/wave/waveFiles/prosze32bit.wav");
	cx *  outdata2 = FastFourierTransform(waveFile2, waveFile2.getNumberOfSamples());
	ASSERT_NE(outdata[0], outdata2[0]);
}
