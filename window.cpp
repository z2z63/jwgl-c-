#include "window.h"
#include <QApplication>
#include <QWidget>
#include <curl/curl.h>
#include <regex>
#include <boost/regex.hpp>
#include <cstring>
#include <iostream>

Window::Window(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    login();
}

void Window::login() {
    return showQrcode();
}

void Window::showQrcode() {
    const char url1[512] = "https://jwgl.ustb.edu.cn/glht/Logon.do?method=randToken";
    char *url2 = new char[512];
    CURL *curl = curl_easy_init();
    char *resp_text = new char[256];
    curl_easy_setopt(curl, CURLOPT_URL, url1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ret_recv_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, resp_text);
    curl_easy_perform(curl);
    std::cout << resp_text << std::endl;
    boost::regex reg1(R"~((?<={"rand_token":")(.*?)(?="))~", boost::regex::JavaScript);
    boost::regex reg2(R"~((?<="appid":")(.*?)(?="}))~", boost::regex::JavaScript);
    boost::cmatch rand_token_matches;
    if (!boost::regex_search(resp_text, rand_token_matches, reg1)) {
        throw std::runtime_error("regular expression matched None : rand_token");
    }
    boost::cmatch appid_matches;
    if (!boost::regex_search(resp_text, appid_matches, reg2)) {
        throw std::runtime_error("regular expression matched None : appid");
    }
    char *appid = new char[appid_matches.length()];
    char *rand_token = new char[rand_token_matches.length()];
    appid_matches.str().copy(appid, appid_matches.length(), 0);
    rand_token_matches.str().copy(rand_token, rand_token_matches.length(), 0);
    std::map<const char *, const char *> params = {
            {"appid",      appid},
            {"return_url", "https://jwgl.ustb.edu.cn/glht/Logon.do?method=weCharLogin"},
            {"rand_token", rand_token},
            {"embed_flag", "1"}
    };
    const char *url_t = "https://sis.ustb.edu.cn/connect/qrpage";
    url_encode(url2, url_t, params);



}


void url_encode(char *dest, const char *origin, std::map<const char *, const char *> params) {
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

size_t ret_recv_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    std::memcpy(stream, ptr, size * nmemb);
    return size * nmemb;
}