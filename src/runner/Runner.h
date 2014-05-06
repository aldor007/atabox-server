/*
 * Runner.h
 *
 *  Created on: 5 maj 2014
 *      Author: aldor
 */

#ifndef RUNNER_H_
#define RUNNER_H_
#include <boost/process.hpp>

class Runner {
public:
	Runner();
	virtual ~Runner();
	virtual int16_t run();
};

#endif /* RUNNER_H_ */
