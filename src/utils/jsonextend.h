/*
 * jsonextend.h
 *
 *  Created on: 8 cze 2014
 *      Author: aldor
 */

#ifndef JSONEXTEND_H_
#define JSONEXTEND_H_

#include <shark/LinAlg/Base.h>
#include "cpprest/json.h"


class jsonextend : public web::json::value {
public:
		operator std::string () const {
			return this->serialize();

		}
		bool operator<( const jsonextend& other) const {
			jsonextend tmp = other;
			jsonextend tmpthis = *this;
        	uint32_t counter_this = 0, counter_other  =  0;
        	counter_this = 0;
			for (auto iter = this->as_object().cbegin(); iter != this->as_object().cend(); ++iter)
				if (other.has_field(iter->first) && tmp[iter->first].is_number()) {
					if (tmp[iter->first].as_double() > tmpthis[iter->first].as_double())
					   counter_other++;
					else
						counter_this++;
				}

			return counter_this < counter_other;
		}
		jsonextend(std::string instring):
			web::json::value(web::json::value::parse(instring.c_str())) {
		}

        jsonextend(std::vector<std::vector<double>> data) {
            size_t i = 0;
            for (auto &d : data) {
				auto arr = web::json::value();

				size_t j = 0;
				for (auto &x: d) {
					arr[j++] = web::json::value::number(x);
				}
				this->operator[](i++) = arr;
            }
        }

        jsonextend(std::vector<double> data) {
            size_t i = 0;
            for (auto &d : data) {
                this->operator[](i++) = web::json::value::number(d);
            }
        }


		template <class T>
	    jsonextend(std::vector<T> data) {
			size_t i = 0;
			for (auto &d : data) {
				this->operator[](i++) = web::json::value(d);
			}
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

		shark::RealVector toRealVector() const {

            size_t size = this->as_object().size() + this->as_object().at("mfcc").size() - 1;
            shark::RealVector data{size};
            const auto mfccArr = this->as_object().at("mfcc").as_array();
            size_t i = 0;
            for (auto iter = this->as_object().cbegin(); iter != this->as_object().cend(); ++iter) {

                if (iter->first == "mfcc") {
                    for (auto mfcc: mfccArr) {
                        data[i] = mfcc.as_double();
                    }

                } else  {
                    if (iter->second.is_double())
                        data[i] = iter->second.as_double();
                    else if (iter->second.is_integer())
                        data[i] = iter->second.as_integer();
                }
                i++;
            }

            return data;

        }

	    std::vector<double> toVector() const {
			std::vector<double> result;
			if (!this->is_array()) {
				return result;
			}

			auto arr = this->as_array();
			result.reserve(arr.size());

			for (auto &v: arr) {
				if (v.is_integer()) {
					result.push_back(v.as_integer());
				} else if (v.is_double()) {
					result.push_back(v.as_double());
				}
			}

			return result;
		};

        void saveToFile(std::string path) {
            std::ofstream out(path);
            out << this->serialize();
            out.close();
        }

        operator shark::RealVector() const {
            return this->toRealVector();
        }

		operator std::vector<double>() const {
			return this->toVector();
		}


		operator std::vector<std::vector<double>>() const {
				std::vector<std::vector<double>> result;
				if (!this->is_array()) {
					return result;
				}

				auto arr = this->as_array();
				result.reserve(arr.size());

				for (auto &v: arr) {
					if (v.is_array()) {
						auto inArr = v.as_array();
						std::vector<double> tmp;
						for (auto &x: inArr) {
							if (x.is_double()) {
								tmp.push_back(x.as_double());
							} else if (x.is_integer()) {
								tmp.push_back(x.as_integer());
							}
						}
						result.push_back(tmp);
					}
				}

				return result;

		};
};

#endif /* JSONEXTEND_H_ */
