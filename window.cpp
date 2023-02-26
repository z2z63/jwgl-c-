#include "window.h"
#include <QApplication>
#include <QWidget>
#include <boost/regex.hpp>
#include <iostream>
#include "session.h"

Window::Window(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    login();
}

void Window::login() {
    return showQrcode();
}

void Window::showQrcode() {
    const char *url1 = "https://jwgl.ustb.edu.cn/glht/Logon.do?method=randToken";
    const char *url2 = "https://sis.ustb.edu.cn/connect/qrpage";
    auto session = WebSession::Session();

    char *resp_text = session.get(url1);
    std::cout << resp_text << std::endl;
    boost::regex reg1(R"~((?<={"rand_token":")(.*?)(?="))~", boost::regex::JavaScript);
    boost::regex reg2(R"~((?<="appid":")(.*?)(?="}))~", boost::regex::JavaScript);
    boost::cmatch rand_token_matches;
    boost::cmatch appid_matches;
    if (!boost::regex_search(resp_text, rand_token_matches, reg1)) {
        throw std::runtime_error("regular expression matched None : rand_token");
    }
    if (!boost::regex_search(resp_text, appid_matches, reg2)) {
        throw std::runtime_error("regular expression matched None : appid");
    }
    char *appid = new char[appid_matches.length()];
    char *rand_token = new char[rand_token_matches.length()];
    appid[appid_matches.length()] = 0;
    rand_token[rand_token_matches.length()] = 0;
    appid_matches.str().copy(appid, appid_matches.length(), 0);
    rand_token_matches.str().copy(rand_token, rand_token_matches.length(), 0);
    std::map<const char *, const char *> params = {
            {"appid",      appid},
            {"return_url", "https://jwgl.ustb.edu.cn/glht/Logon.do?method=weCharLogin"},
            {"rand_token", rand_token},
            {"embed_flag", "1"}
    };
    resp_text = session.get(url2, params);
    std::cout << resp_text << std::endl;

}


