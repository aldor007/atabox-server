/*
 * DanielsonLanczos.h
 *
 *  Created on: 19 kwi 2014
 *      Author: aldor
 */

#ifndef DANIELSONLANCZOS_H_
#define DANIELSONLANCZOS_H_
#include <complex>
// TODO: delete class
class DanielsonLanczos {
	 DanielsonLanczos *  next;
	 unsigned int N;
public:
	DanielsonLanczos(unsigned int  N = 0);
	virtual ~DanielsonLanczos();
	void apply(std::complex<double> * data);
};

#endif /* DANIELSONLANCZOS_H_ */
