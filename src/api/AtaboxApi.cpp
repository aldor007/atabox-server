/*
 * AtaboxApi.cpp
 *
 *  Created on: 21 kwi 2014
 *      Author: aldor
 */

#include "AtaboxApi.h"
using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
std::string AtaboxApi::m_apiMainPath = "api";

AtaboxApi::AtaboxApi(std::string host, std::string port) {
	// TODO Auto-generated constructor stub
	m_url = U("http://");
	m_url.append(host);
	m_url.append(":");
	m_url.append(port);
	m_url.append(m_apiMainPath);
	m_host = host;
	m_port = port;
	m_listener = http_listener(m_url);
	auto tmp_get = std::bind(&AtaboxApi::handle_get, this, std::placeholders::_1);
//m_listener.support(methods::GET, std::tr1::bind(&AtaboxApi::handle_get, this, std::tr1::placeholders::_1));
//m_listener.support(methods::GET, tmp_get);
  //m_listener.support(methods::GET, &handle_get);
   // m_listener.support(methods::POST, std::bind(&AtaboxApi::handle_post, this, std::placeholders::_1));


}
AtaboxApi::AtaboxApi(utility::string_t url): m_listener(url) {
	// TODO Auto-generated constructor stub
	m_url = url;
	auto tmp_get = std::bind(&AtaboxApi::handle_get, this, std::placeholders::_1);
//m_listener.support(methods::GET, std::tr1::bind(&AtaboxApi::handle_get, this, std::tr1::placeholders::_1));
m_listener.support(methods::GET, tmp_get);
  //m_listener.support(methods::GET, &handle_get);
   // m_listener.support(methods::POST, std::bind(&AtaboxApi::handle_post, this, std::placeholders::_1));


}

AtaboxApi::~AtaboxApi() {
	// TODO Auto-generated destructor stub
}


void AtaboxApi::handle_error(pplx::task<void>& t)
{
    try
    {
        t.get();
    }
    catch(...)
    {
        // Ignore the error, Log it if a logger is available
    }
}

pplx::task<void> AtaboxApi::open()
{
  //  return m_listener.open().then(std::bind(&handle_error, std::placeholders::_1));
   return m_listener.open().then([]()
        {
            //...
        });
}

pplx::task<void> AtaboxApi::close()
{
    //return m_listener.close().then(std::bind(&handle_error, std::placeholders::_1));
}

// Handler to process HTTP::GET requests.
// Replies to the request with data.
void AtaboxApi::handle_get(http_request request)
{
    auto path = request.relative_uri().path();
   auto content_data = m_router.find(path);
    if (content_data == m_router.end())
    {
        request.reply(status_codes::NotFound, U("Path not found"));
        return;
    }

    //auto tmp_fun = m_router[content_data];
    //tmp_fun(request);
}

// Respond to HTTP::POST messages
// Post data will contain the postal code or location string.
// Aggregate location data from different services and reply to the POST request.
void AtaboxApi::handle_post(http_request request)
{
    auto path = request.relative_uri().path();
    auto content_data = m_router.find(path);
    if (content_data == m_router.end())
    {
        request.reply(status_codes::NotFound, U("Path not found"));
        return;
    }

   // auto apiRequest = std::get<0>(content_data->second);
   // m_router[apiRequest](request);*/
}

