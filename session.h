
#ifndef UNTITLED_SESSION_H
#define UNTITLED_SESSION_H
#define BUFFERSIZE 4096

#include <curl/curl.h>
#include <map>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cstdio>
using namespace std;
namespace WebSession {
    class Session;

    class Response {
    public:
        explicit Response(Session &session);

        void writeFile(const string& fileName);

        string *text();

    private:
        CURL *curl;
        string *buffer_ptr;
        string *url_with_params;
    };

    class Session {
    public:
        Session();

        ~Session();

        Response get(string &url, const map<const string, const string> &params = {});

        friend Response::Response(Session &session);

    private:
        CURL *curl;
        string text_buffer{};

        string url_with_params{};
    };


    void url_encode(string *dest, string &origin, const map<const string, const string> &params);

    size_t ret_recv_text(void *ptr, size_t size, size_t nmemb, void *stream);

}

#endif //UNTITLED_SESSION_H
