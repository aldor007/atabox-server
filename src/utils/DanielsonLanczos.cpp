/*
 * DanielsonLanczos.cpp
 *
 *  Created on: 19 kwi 2014
 *      Author: aldor
 */

#include "DanielsonLanczos.h"
#include <cmath>
#include <complex>
#include <iostream>

template<unsigned M, unsigned N, unsigned B, unsigned A>
struct SinCosSeries {
   static double value() {
      return 1-(A*M_PI/B)*(A*M_PI/B)/M/(M+1)
               *SinCosSeries<M+2,N,B,A>::value();
   }
};

template<unsigned N, unsigned B, unsigned A>
struct SinCosSeries<N,N,B,A> {
   static double value() { return 1.; }
};

template<unsigned B, unsigned A, typename T=double>
struct Sin;

template<unsigned B, unsigned A>
struct Sin<B,A,float> {
   static float value() {
      return (A*M_PI/B)*SinCosSeries<2,24,B,A>::value();
   }
};
template<unsigned B, unsigned A>
struct Sin<B,A,double> {
   static double value() {
      return (A*M_PI/B)*SinCosSeries<2,34,B,A>::value();
   }
};

template<unsigned B, unsigned A, typename T=double>
struct Cos;

template<unsigned B, unsigned A>
struct Cos<B,A,float> {
   static float value() {
      return SinCosSeries<1,23,B,A>::value();
   }
};

template<unsigned B, unsigned A>
struct Cos<B,A,double> {
   static double value() {
      return SinCosSeries<1,33,B,A>::value();
   }
};

DanielsonLanczos::DanielsonLanczos(unsigned int N ) {

	// TODO Auto-generated constructor stub
  this->N = N;
  std::cout<<"N = "<<N;
 if (this->N)
  this->next = new DanielsonLanczos(N/2);


}

DanielsonLanczos::~DanielsonLanczos() {
	// TODO Auto-generated destructor stub
}
void DanielsonLanczos::apply(std::complex<double>* data) {
    if (N == 0) return;
	this->next->apply(data);
     this->next->apply(data + N);

    // double wtemp =  sin(M_PI/N);// -Sin<N, 1, std::complex<double>>::value();// sin(M_PI/N);
     std::complex<double> temp(0,0), w(1.0, 0.0),
//    		 wp( -2.0 * wtemp * wtemp, -Sin<N, 2, std::complex<double>>::value());
    		// wp( -2.0 * wtemp * wtemp, -sin(2*M_PI/N));
		 wp= exp(-std::complex<double>(0,-1) * (M_PI / N));
     //wpr = -2.0*wtemp*wtemp;
     //wpi = -Sin<N, 2, T>::value();//-sin(2*M_PI/N);
     //wr = 1.0;
     //wi = 0.0;
     for (unsigned i=0; i<N; i++) {
       //temp.real( )
       temp = data[i + N ] * w ;
       data[i + N] = data[i] - temp;
       data[i] = data[i] +  temp;

       w = w + w * wp;
     }
}

