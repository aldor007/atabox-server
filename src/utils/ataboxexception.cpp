#include "utils/ataboxexception.h"

ataboxException::ataboxException(std::string msg) throw() {
    m_msg = msg;
}
/**
 *
 */
const char * ataboxException::what() const throw() {
    return m_msg.c_str();
}
/**
 *
 */
ataboxException::~ataboxException() throw(){

}