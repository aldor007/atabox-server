/*
 * ataboxexception.h
 *
 *  Created on: 11 cze 2014
 *      Author: aldor
 */

#ifndef ATABOXEXCEPTION_H_
#define ATABOXEXCEPTION_H_

#include <exception>
#include <string>

#ifndef _GLIBCXX_USE_NOEXCEPT
#define _NO_EXC_AL _NO_EXCEPT
#else
#define _NO_EXC_AL _GLIBCXX_USE_NOEXCEPT
#endif

class ataboxException :public  std::exception {
private:
	std::string m_msg;
public:
	ataboxException(std::string msg) throw();
    virtual const char* what() const throw();
    virtual ~ataboxException() throw();
};



#endif /* ATABOXEXCEPTION_H_ */
