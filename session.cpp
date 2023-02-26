#include "session.h"

WebSession::Session::Session() {
    buffer = new char[BUFFERSIZE];
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
}

WebSession::Session::~Session() {
    delete[] buffer;
    curl_easy_cleanup(curl);
}

char *WebSession::Session::get(const char *url, const std::map<const char *, const char *> &params) {
    memset(buffer, 0, BUFFERSIZE * sizeof(char));
    char url_with_params[512];
    WebSession::url_encode(url_with_params, url, params);
    curl_easy_setopt(curl, CURLOPT_URL, url_with_params);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WebSession::ret_recv_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
    curl_easy_perform(curl);
    return buffer;
}


void WebSession::url_encode(char *dest, const char *origin, const std::map<const char *, const char *> &params) {
    if(params.empty()){
        strcpy(dest, origin);
        return;
    }
    std::ostringstream escaped;
    escaped.str("");
    escaped << origin;
    escaped << '?';
    for (auto i = params.begin(); i != params.end(); i++) {
        escaped << i->first;
        escaped << '=';
        escaped << curl_easy_escape(nullptr, i->second, 0);
        if (i != params.end().operator--()) {
            escaped << '&';
        }
    }
    escaped.str().copy(dest, escaped.str().length(), 0);
}

size_t WebSession::ret_recv_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    std::memcpy(stream, ptr, size * nmemb);
    return size * nmemb;
}

