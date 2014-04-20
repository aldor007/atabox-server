/*
 * DanielsonLanczos.h
 *
 *  Created on: 19 kwi 2014
 *      Author: aldor
 */

#ifndef DANIELSONLANCZOS_H_
#define DANIELSONLANCZOS_H_
#include <complex>

template<unsigned N, typename T=double>
class DanielsonLanczos {
	 DanielsonLanczos<N/2,T> next;
public:
	DanielsonLanczos();
	virtual ~DanielsonLanczos();
	void apply(T * data);
};


#endif /* DANIELSONLANCZOS_H_ */
