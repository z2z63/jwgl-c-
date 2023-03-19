#include "session.h"

using namespace std;

WebSession::Session::Session() {
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
}

WebSession::Session::~Session() {
    curl_easy_cleanup(curl);
}

WebSession::Response WebSession::Session::get(string &url, const map<const string, const string> &params) {
    text_buffer.clear();
    WebSession::url_encode(&url_with_params, url, params);
    return Response(*this);
}


void WebSession::url_encode(string *dest, string &origin, const map<const string, const string> &params) {
    dest->clear();
    if (params.empty()) {
        dest->append(origin);
        return;
    }
    std::ostringstream escaped;
    escaped.str("");
    escaped << origin;
    escaped << '?';
    for (auto i = params.begin(); i != params.end(); i++) {
        escaped << i->first;
        escaped << '=';
        escaped << curl_easy_escape(nullptr, i->second.c_str(), 0);
        if (i != params.end().operator--()) {
            escaped << '&';
        }
    }
    dest->append(escaped.str());
}

size_t WebSession::ret_recv_text(void *ptr, size_t size, size_t nmemb, void *stream) {
    ((string *) stream)->append((const char *) ptr);
    return size * nmemb;
}


WebSession::Response::Response(WebSession::Session &session) {
    curl = session.curl;
    buffer_ptr = &session.text_buffer;
    url_with_params = &session.url_with_params;
}

void WebSession::Session::saveCookies() const {
    curl_easy_setopt(curl, CURLOPT_COOKIELIST, "FLUSH");
}

void WebSession::Response::writeFile(const string& fileName) {
    FILE *fp = fopen(fileName.c_str(), "w");
    if (fp == nullptr) {
        throw runtime_error("File can't open: " + fileName);
    }
    curl_easy_setopt(curl, CURLOPT_URL, url_with_params->c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, nullptr);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    if(curl_easy_perform(curl)){
        throw runtime_error("NetworkError url: " + *url_with_params);
    }
    fclose(fp);
}

string *WebSession::Response::text() {
    curl_easy_setopt(curl, CURLOPT_URL, url_with_params->c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WebSession::ret_recv_text);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer_ptr);
    CURLcode code = curl_easy_perform(curl);
    if(code){
        throw runtime_error("NetworkError url: " + *url_with_params + curl_easy_strerror(code));
    }
//    cout << *url_with_params << endl;
//    cout << "Code: " << curl_easy_strerror(code);
    return buffer_ptr;
}
