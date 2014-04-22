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
std::string AtaboxApi::m_apiMainPath = "/api/";

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
	listenerSetSupports();
}
void AtaboxApi::addMethod(std::string name, handle_request_fun fun) {
	m_router[name] = fun;
}
/*
AtaboxApi::AtaboxApi(utility::string_t url): m_listener(url) {
	m_url = url;
	url.
	auto tmpTab = url.substr();
	tmptab[1].erase(0, 2);
	m_host = tmptab[1];
	m_port = tmptab[2];
	listenerSetSupports();
}
*/
void  AtaboxApi::listenerSetSupports() {
	m_listener.support(methods::GET, std::bind(&AtaboxApi::handle_get, this, std::placeholders::_1));
	m_listener.support(methods::POST, std::bind(&AtaboxApi::handle_post, this, std::placeholders::_1));
	m_listener.support(methods::PUT, std::bind(&AtaboxApi::handle_put, this, std::placeholders::_1));

}
AtaboxApi::~AtaboxApi() {
	// TODO Auto-generated destructor stub
	m_listener.close();
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
    return m_listener.close();
}

void AtaboxApi::commonHandler(http_request request) {

    auto path = request.relative_uri().path();
   auto handle_fun = m_router.find(path);
    if (handle_fun == m_router.end())
    {
        request.reply(status_codes::NotFound, U("Path not found"));
        return;
    }
    (handle_fun->second)(request);
}
// Handler to process HTTP::GET requests.
// Replies to the request with data.
void AtaboxApi::handle_get(http_request request)
{
	commonHandler(request);
}

// Respond to HTTP::POST messages
// Post data will contain the postal code or location string.
// Aggregate location data from different services and reply to the POST request.
void AtaboxApi::handle_post(http_request request)
{
	commonHandler(request);
}

void AtaboxApi::handle_put(http_request request)
{
	commonHandler(request);
}

