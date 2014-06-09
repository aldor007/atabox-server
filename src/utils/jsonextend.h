/*
 * jsonextend.h
 *
 *  Created on: 8 cze 2014
 *      Author: aldor
 */

#ifndef JSONEXTEND_H_
#define JSONEXTEND_H_
#include "cpprest/json.h"


class jsonextend : public web::json::value {
public:
		operator std::string () const {
			return this->to_string();

		}
		bool operator<( const jsonextend& other) const {
			if (this->size() > other.size())
				return true;
			return false;
		}
		jsonextend(std::string instring):
			web::json::value(web::json::value::parse(instring.c_str())) {
		}
		/*jsonextend(std::string& instring):
			web::json::value(web::json::value::parse(instring.c_str())) {
		}*/
		jsonextend():web::json::value() {

		}
        bool operator==(const jsonextend& other) const {
			return static_cast<web::json::value>(*this) ==
					static_cast<web::json::value>(other);
		}

        bool operator!=(const jsonextend& other) const
        {
			return static_cast<web::json::value>(*this) !=
					static_cast<web::json::value>(other);
        }
        jsonextend& operator+=(const jsonextend& second) {
        	if (second.is_null())
        		return *this;
        	for (auto iter = second.as_object().cbegin(); iter != second.as_object().cend(); iter++)
        	   this->operator [](iter->first) = web::json::value(iter->second);
        	return *this;
        }
        jsonextend operator+(const jsonextend& second) {
        	jsonextend first;
        	if (second.is_null())
        		return first;
        	for (auto iter = this->as_object().cbegin(); iter != this->as_object().cend(); iter++)
        	   first[iter->first] = iter->second;
        	for (auto iter = second.as_object().cbegin(); iter != second.as_object().cend(); iter++)
        	   first[iter->first] = iter->second;

        	return first;
        }
};



#endif /* JSONEXTEND_H_ */
