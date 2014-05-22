/*
 * atabox_log.cpp
 *
 *  Created on: 22 maj 2014
 *      Author: aldor
 */
#include <fstream>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/phoenix/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/utility/value_ref.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/empty_deleter.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/expressions/formatters/if.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/attr.hpp>

#include "utils/atabox_log.h"



atabox_log::logger g_log;

namespace atabox_log {
    boost::shared_ptr<atabox_log::mutable_string_mt> file_attr(new atabox_log::mutable_string_mt(""));
    boost::shared_ptr<atabox_log::mutable_string_mt> function_attr(new atabox_log::mutable_string_mt(""));
    boost::shared_ptr<atabox_log::mutable_int_mt> line_attr(new atabox_log::mutable_int_mt(1));

    BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
    BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)
    BOOST_LOG_ATTRIBUTE_KEYWORD(tag_attr, "Tag", std::string)
    BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
    BOOST_LOG_ATTRIBUTE_KEYWORD(scopes, "Scopes", boost::log::attributes::named_scope)

    void init_logging() {
        namespace logging = boost::log;
        namespace src = boost::log::sources;
        namespace expr = boost::log::expressions;
        namespace sinks = boost::log::sinks;
        namespace attrs = boost::log::attributes;
        namespace keywords = boost::log::keywords;
        boost::shared_ptr< logging::core > core = logging::core::get();

        // Create a backend and attach a couple of streams to it
        typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
           boost::shared_ptr< text_sink > backend = boost::make_shared< text_sink >();
        backend->locked_backend()->add_stream(boost::shared_ptr< std::ostream >(&std::clog, logging::empty_deleter()));

      //  backend->locked_backend()->add_stream(boost::make_shared< std::ofstream >("testapp.log"));
        //TODO: log to file, active colors on paramter
        logging::formatter frm =
            expr::stream
            << expr::if_(expr::attr<severity_level>("Severity") == error)[
                 expr::stream<< "\x1b[31m"
                 ]
            << expr::if_(expr::attr<severity_level>("Severity") == info) [
                expr::stream<< "\x1b[32m"
                ]

            << expr::if_(expr::attr<severity_level>("Severity") == warning) [
                expr::stream<< "\x1b[33m"
                ]

            << expr::if_(expr::attr<severity_level>("Severity") == debug) [
                expr::stream<< "\x1b[34m"
                ]
            << expr::if_(expr::attr<severity_level>("Severity") == fatal) [
                expr::stream<< "\x1b[35m"
                ]
           <<  "["<<expr::format_date_time< boost::posix_time::ptime >("TimeStamp", std::string("%Y-%m-%d %H:%M:%S"))
           << "] ["
            <<  expr::attr<boost::log::attributes::current_process_id::value_type >("ProcessID")
            << "."
            <<  expr::attr<boost::log::attributes::current_thread_id::value_type >("ThreadID")
            << "] "
            << "("<<
            expr::attr< std::string >("Function")
            << ":"
            << expr::attr< std::string >("File")
            << ":"
            << expr::attr<int >("Line")
            << ") ["
            << expr::attr<severity_level>("Severity")
            << "] " << expr::smessage << "\x1b[0m";
        backend->set_formatter(frm);

        logging::add_common_attributes();
        // Enable auto-flushing after each log record written
        backend->locked_backend()->auto_flush(true);

        // Wrap it into the frontend and register in the core.
        // The backend requires synchronization in the frontend.
        core->add_sink(backend);
        core->add_global_attribute("Scope", attrs::named_scope());
        g_log.add_attribute("File", *atabox_log::file_attr);
        g_log.add_attribute("Line", *atabox_log::line_attr);
        g_log.add_attribute("Function", *atabox_log::function_attr);

    }
}


