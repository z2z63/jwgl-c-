
#ifndef UNTITLED_SESSION_H
#define UNTITLED_SESSION_H
#define BUFFERSIZE 4096

#include <curl/curl.h>
#include <map>
#include <cstring>
#include <iostream>
#include <sstream>


namespace WebSession {
    class Session {
    public:
        Session();

        ~Session();

        char *get(const char *url, const std::map<const char *, const char *> &params = {});

    private:
        CURL *curl;
        char *buffer;
    };

    void url_encode(char *dest, const char *origin, const std::map<const char *, const char *> &params);

    size_t ret_recv_data(void *ptr, size_t size, size_t nmemb, void *stream);
}

#endif //UNTITLED_SESSION_H
