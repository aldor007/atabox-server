/*
 * DanielsonLanczos.cpp
 *
 *  Created on: 19 kwi 2014
 *      Author: aldor
 */

#include "DanielsonLanczos.h"
#include <cmath>
#include <complex>

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

template<unsigned N, typename T>
DanielsonLanczos<N, T>::DanielsonLanczos() {
	// TODO Auto-generated constructor stub
//	this->next =

}

template<unsigned N, typename T>
DanielsonLanczos<N, T>::~DanielsonLanczos() {
	// TODO Auto-generated destructor stub
}
template<unsigned N, typename T>
void DanielsonLanczos<N, T>::apply(T* data) {
     this->next.apply(data);
     this->next.apply(data + N);

     T wtemp,tempr,tempi,wr,wi,wpr,wpi;
     wtemp = -Sin<N, 1, T>::value();// sin(M_PI/N);
     wpr = -2.0*wtemp*wtemp;
     wpi = -Sin<N, 2, T>::value();//-sin(2*M_PI/N);
     wr = 1.0;
     wi = 0.0;
     for (unsigned i=0; i<N; i+=2) {
       tempr = data[i + N] * wr - data[i + N + 1] * wi;
       tempi = data[i + N] * wi + data[i + N + 1] * wr;
       data[i + N] = data[i] - tempr;
       data[i + N + 1] = data[i + 1] - tempi;
       data[i] += tempr;
       data[i + 1] += tempi;

       wtemp = wr;
       wr += wr * wpr - wi*wpi;
       wi += wi * wpr + wtemp*wpi;
     }
}
