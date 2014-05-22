/*
 * atabox_log.h
 *
 *  Created on: 22 maj 2014
 *      Author: aldor
 */

#ifndef ATABOX_LOG_H_
#define ATABOX_LOG_H_


#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/thread/shared_lock_guard.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <mutex>

enum severity_level {
    debug = -1,
    info = 0,
    warning,
    error,
    fatal
};

namespace atabox_log {
    typedef boost::log::attributes::mutable_constant<int, boost::shared_mutex,
    		boost::shared_lock_guard< boost::shared_mutex > > mutable_int_mt;
   typedef boost::log::attributes::mutable_constant<std::string, boost::shared_mutex,
		   boost::shared_lock_guard< boost::shared_mutex > > mutable_string_mt;
   typedef boost::log::sources::severity_logger<severity_level> logger;
   extern boost::shared_ptr<mutable_string_mt> file_attr;
    extern boost::shared_ptr<mutable_string_mt> function_attr;
    extern boost::shared_ptr<mutable_int_mt> line_attr;

    template<typename T>
        static inline T& tag_log_location
        (T &log_,
         const std::string file_,
         int line_,
         const std::string function_) {
    		atabox_log::file_attr->set(file_);
    		atabox_log::function_attr->set(function_);
    		atabox_log::line_attr->set(line_);
        return log_;
    }

    void init_logging();
}

extern atabox_log::logger g_log;
#define LOG(lvl_) BOOST_LOG_SEV(atabox_log::tag_log_location(g_log, __FILE__, __LINE__, __FUNCTION__), lvl_)


template< typename CharT, typename TraitsT >
    inline std::basic_ostream< CharT, TraitsT >& operator<<
    (std::basic_ostream< CharT, TraitsT >& strm, severity_level level) {
    static const char* const str[] = {
        "debug",
        "info",
        "warning",
        "error",
        "fatal"
    };
    if(level >= debug && level <= fatal) {
          strm      << str[level - debug];
    } else {
        strm << static_cast<int>(level);
    }
    return strm;
}




#endif /* ATABOX_LOG_H_ */
