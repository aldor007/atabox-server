#include <complex>
#include <cmath>
#include <valarray>
#include <utility>

#include "wave/WaveFile.h"
#include "wave/processing/postprocessing/FastFourierTransformFilter.h"
#ifndef GTEST_H_
	#define GTEST_H_
	#include "gtest/gtest.h"
#endif

class FastFourierTransformFilterTest: public ::testing::Test {
public:
	FastFourierTransformFilter fftFilter;

};

TEST_F(FastFourierTransformFilterTest, exampleDataStacv) {
	//given
	typedef std::complex<double> cx;
	cx * input = new cx[8];
	 input[0] = 0.0;
	    input[1] = 162.6345596729059;
	    input[2] = 230.0;
	    input[3] = 162.63455967290594;
	    input[4] = 2.8166876380389125E-14;
	    input[5] = -162.6345596729059;
	    input[6] = -230.0;
	    input[7] = -162.63455967290597;
	fftFilter.applyOn(input, 8);
  ASSERT_EQ(std::abs(input[1]), 920);
  ASSERT_EQ(std::abs(input[0]),  2.5483305001488234E-16);
  delete[] input;

}
TEST_F(FastFourierTransformFilterTest, exampleDataBlog) {
	//given
	typedef std::complex<double> cx;
	cx indata[] =  { cx(0,0), cx(1,1), cx(3,3), cx(4,4),
			cx(4, 4), cx(3, 3), cx(1,1), cx(0,0) };
	  std::valarray<cx> test(indata, 8);
	fftFilter.applyOn(indata, 8);
	ASSERT_EQ(indata[0], cx(16, 16));
  ASSERT_EQ(indata[2], cx(0,0));


}
TEST_F(FastFourierTransformFilterTest, exampleDataWolfram) {
	//given
	typedef std::complex<double> cx;
	cx indata[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
	fftFilter.applyOn(indata, 8);
	ASSERT_EQ(indata[0], cx(4,0));


}

TEST_F(FastFourierTransformFilterTest, D2ISABLED_TheSameWaveData) {
	//given
	typedef std::complex<double> cx;
	WaveFile waveFile("test/wave/waveFiles/dziekuje32bit.wav");
	//std::vector<cx> outdata;
   Samples samplesFile(waveFile);
  fftFilter.applyOn(samplesFile);

	WaveFile waveFile2("test/wave/waveFiles/dziekuje32bit.wav");
	Samples samplesFile2(waveFile);
   fftFilter.applyOn(samplesFile2);
	ASSERT_EQ(samplesFile[0], samplesFile2[0]);

}

TEST_F(FastFourierTransformFilterTest, furier440Hz200Hz) {
	//given
	typedef std::complex<double> cx;
	WaveFile waveFile("test/wave/waveFiles/440Hz200Hz200ms.wav");
	Samples samplesFile(std::move(waveFile));
  fftFilter.applyOn(samplesFile);

  //   ASSERT_EQ(outdata[0], cx(4.21362,0));

}
TEST_F(FastFourierTransformFilterTest, furier440Hz) {
	//given
	typedef std::complex<double> cx;
	WaveFile waveFile("test/wave/waveFiles/440Hz200ms.wav");
	Samples samplesFile(std::move(waveFile));
  fftFilter.applyOn(samplesFile);

	//ASSERT_EQ(outdata[0], cx(9.51086,0));

}
TEST_F(FastFourierTransformFilterTest, DI2SABLED_timetranformofdziekuje) {
	//given
	typedef std::complex<double> cx;
	WaveFile waveFile("test/wave/waveFiles/dziekuje32bit.wav");
	Samples samplesFile(waveFile);
	//std::vector<cx> outdata;

     fftFilter.applyOn(samplesFile);


	ASSERT_EQ(samplesFile[0], samplesFile[0]);
}
TEST_F(FastFourierTransformFilterTest, DIS2ABLED_DiffrentWaveData) {
	//given
	typedef std::complex<double> cx;
	WaveFile waveFile("test/wave/waveFiles/dziekuje32bit.wav");
	Samples samplesFile(waveFile);
	//std::vector<cx> outdata;

     fftFilter.applyOn(samplesFile);

	WaveFile waveFile2("test/wave/waveFiles/prosze32bit.wav");
	Samples samplesFile2(waveFile2);
     fftFilter.applyOn(samplesFile2);
	ASSERT_NE(samplesFile[0], samplesFile2[0]);
}

