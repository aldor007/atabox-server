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

};



#endif /* JSONEXTEND_H_ */
