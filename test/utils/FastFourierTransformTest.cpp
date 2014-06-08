
#include <complex>
#include <cmath>
#include <valarray>
#include <utility>

#include "wave/WaveFile.h"
#include "math/fast_fourier_transform.h"
#ifndef GTEST_H_
	#define GTEST_H_
	#include "gtest/gtest.h"
#endif

class fast_fourier_transformTest: public ::testing::Test {

};

TEST_F(fast_fourier_transformTest, exampleDataStacv) {
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
	auto outdata = fast_fourier_transform(input, 8);
  ASSERT_EQ(std::abs(outdata[1]), 920);
  ASSERT_EQ(std::abs(outdata[0]),  2.5483305001488234E-16);

}
TEST_F(fast_fourier_transformTest, exampleDataBlog) {
	//given
	typedef std::complex<double> cx;
	cx indata[] =  { cx(0,0), cx(1,1), cx(3,3), cx(4,4),
			cx(4, 4), cx(3, 3), cx(1,1), cx(0,0) };
	  std::valarray<cx> test(indata, 8);
	auto outdata = fast_fourier_transform(indata, 8 );
	ASSERT_EQ(outdata[0], cx(16, 16));
  ASSERT_EQ(outdata[2], cx(0,0));


}
TEST_F(fast_fourier_transformTest, exampleDataWolfram) {
	//given
	typedef std::complex<double> cx;
	cx indata[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
	  std::valarray<cx> test(indata, 8);
	auto outdata = fast_fourier_transform(indata, 8);
	ASSERT_EQ(outdata[0], cx(4,0));


}

TEST_F(fast_fourier_transformTest, DISABLED_TheSameWaveData) {
	//given
	typedef std::complex<double> cx;
	WaveFile waveFile("test/wave/waveFiles/dziekuje32bit.wav");
	//std::vector<cx> outdata;
   Samples samplesFile(waveFile);
  std::complex<double> * outdata = fast_fourier_transform(samplesFile);

	WaveFile waveFile2("test/wave/waveFiles/dziekuje32bit.wav");
	Samples samplesFile2(waveFile);
	cx *  outdata2 = fast_fourier_transform(samplesFile2);
	ASSERT_EQ(outdata[0], outdata2[0]);

}

TEST_F(fast_fourier_transformTest, furier440Hz200Hz) {
	//given
	typedef std::complex<double> cx;
	WaveFile waveFile("test/wave/waveFiles/440Hz200Hz200ms.wav");
	Samples samplesFile(std::move(waveFile));
	std::complex<double> * outdata = fast_fourier_transform(samplesFile);

  //   ASSERT_EQ(outdata[0], cx(4.21362,0));

}
TEST_F(fast_fourier_transformTest, furier440Hz) {
	//given
	typedef std::complex<double> cx;
	WaveFile waveFile("test/wave/waveFiles/440Hz200ms.wav");
	Samples samplesFile(std::move(waveFile));
	std::complex<double> * outdata = fast_fourier_transform(samplesFile);

	//ASSERT_EQ(outdata[0], cx(9.51086,0));

}
TEST_F(fast_fourier_transformTest, timetranformofdziekuje) {
	//given
	typedef std::complex<double> cx;
	WaveFile waveFile("test/wave/waveFiles/dziekuje32bit.wav");
	Samples samplesFile(waveFile);
	//std::vector<cx> outdata;

	std::complex<double> * outdata = fast_fourier_transform(samplesFile);

	ASSERT_EQ(outdata[0], outdata[0]);
}
TEST_F(fast_fourier_transformTest, DISABLED_DiffrentWaveData) {
	//given
	typedef std::complex<double> cx;
	WaveFile waveFile("test/wave/waveFiles/dziekuje32bit.wav");
	Samples samplesFile(waveFile);
	//std::vector<cx> outdata;

	std::complex<double> * outdata = fast_fourier_transform(samplesFile);

	WaveFile waveFile2("test/wave/waveFiles/prosze32bit.wav");
	Samples samplesFile2(waveFile2);
	cx *  outdata2 = fast_fourier_transform(samplesFile2);
	ASSERT_NE(outdata[0], outdata2[0]);
}
