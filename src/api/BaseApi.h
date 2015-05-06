
#ifndef _BASE_API_H
#define _BASE_API_H

class BaseApi
{
public:
    typedef void (* handle_request_fun)(web::http::http_request&);
    BaseApi(std::string host, std::string port);
    BaseApi(utility::string_t url);
    virtual ~BaseApi();
    pplx::task<void> open();
    pplx::task<void> close();
    void addMethod(std::string name, handle_request_fun fun);
    std::map<utility::string_t, handle_request_fun> getMethods() const;
protected:
    static void handle_error(pplx::task<void>&t);
    void  inline listenerSetSupports();
    void inline commonHandler(web::http::http_request&);
    bool inline staticFilesHandler(web::http::http_request&);
    void handle_get(web::http::http_request);
    void handle_post(web::http::http_request);
    void handle_put(web::http::http_request);
    std::map<utility::string_t, handle_request_fun> m_router;
    std::string m_host;
    std::string m_port;
    utility::string_t m_url;
    web::http::experimental::listener::http_listener m_listener;
    std::map<utility::string_t, std::tuple<utility::string_t, utility::string_t>> m_htmlcontentmap;
};
 
#endif