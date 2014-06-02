/*
 * AtaboxApi.cpp
 *
 *  Created on: 21 kwi 2014
 *      Author: aldor
 */

#include "AtaboxApi.h"
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
std::string AtaboxApi::m_apiMainPath = "/api/";

AtaboxApi::AtaboxApi(std::string host, std::string port) {
	m_url = U("http://");
	m_url.append(host);
	m_url.append(":");
	m_url.append(port);
	m_url.append(m_apiMainPath);
}
void AtaboxApi::addMethod(std::string name, handle_request_fun fun) {
	m_router[name] = fun;
}

AtaboxApi::AtaboxApi(utility::string_t url) {
	m_url = U("http://");
	m_url.append(url);
	m_url.append(m_apiMainPath);
}

void  AtaboxApi::listenerSetSupports() {
	//m_listener.configuration().set_timeout()
	m_listener = http_listener(m_url);
	m_listener.support(methods::GET, std::bind(&AtaboxApi::handle_get, this, std::placeholders::_1));
	m_listener.support(methods::POST, std::bind(&AtaboxApi::handle_post, this, std::placeholders::_1));
	m_listener.support(methods::PUT, std::bind(&AtaboxApi::handle_put, this, std::placeholders::_1));

}
AtaboxApi::~AtaboxApi() {
	m_listener.close();
}

std::map<utility::string_t, handle_request_fun> AtaboxApi::getMethods() {
	return m_router;
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
	listenerSetSupports();
   return m_listener.open().then([]()
        {
            //...
	   	   LOG(debug)<<"Open listener";
        });
}

pplx::task<void> AtaboxApi::close()
{
	LOG(debug)<<"IN close";
    return m_listener.close().then([](){

  	   LOG(debug)<<"Close listener";
    });
}

void AtaboxApi::commonHandler(http_request request) {

    auto path = request.relative_uri().path();
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));

    auto handle_fun = m_router.find(paths[0]);
    LOG(debug) <<"Path "<<path<<" "<<paths[0];//<<" q "<<queryItr->second;
    if (handle_fun == m_router.end())
    {
    	LOG(debug) <<"Path "<<path<<" "<<paths[0];//<<" q "<<queryItr->second;
        request.reply(status_codes::NotFound, U("Path not found"));

        return;

    }
    (handle_fun->second)(request);
}
// Handler to process HTTP::GET requests.
// Replies to the request with data.
void AtaboxApi::handle_get(http_request request)
{
    LOG(debug) <<" Handle GET method";
	commonHandler(request);
}

// Respond to HTTP::POST messages
// Post data will contain the postal code or location string.
// Aggregate location data from different services and reply to the POST request.
void AtaboxApi::handle_post(http_request request)
{
    LOG(debug) <<" Handle POST method";
	commonHandler(request);
}

void AtaboxApi::handle_put(http_request request)
{
	commonHandler(request);
}

