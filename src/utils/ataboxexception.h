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

class ataboxException :public  std::exception {
private:
	std::string m_msg;
public:
	ataboxException(std::string msg): m_msg(msg) {

	}
    virtual const char* what() const _GLIBCXX_USE_NOEXCEPT {
    	return m_msg.c_str();
    }
    virtual ~ataboxException() {

    }
};



#endif /* ATABOXEXCEPTION_H_ */
