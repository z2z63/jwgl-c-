#include "window.h"
#include <QWidget>
#include <boost/regex.hpp>
#include <iostream>
#include "session.h"
#include "holdTcp.h"

Window::Window(QWidget *parent) : QMainWindow(parent) {
    worker = new holdTcp();
    ui.setupUi(this);
    ofstream f;
    f.open("cookies.txt", ofstream::out|std::ofstream::trunc);
    f.close();
    connect(this, &Window::operate, worker, &holdTcp::HoldTcpAndLogin);
    connect(&thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(worker, &holdTcp::resultReady, this, &Window::selectCourse);
    login();
}

void Window::login() {
    return showQrcode();
}

void Window::showQrcode() {
    string url1 = "https://jwgl.ustb.edu.cn/glht/Logon.do?method=randToken";
    string url2 = "https://sis.ustb.edu.cn/connect/qrpage";
    string url3 = "https://sis.ustb.edu.cn/connect/qrimg";
    WebSession::Session session;
    string *resp_text = session.get(url1).text();
    cout << *resp_text << endl;
    boost::regex reg1((R"~((?<={"rand_token":")(.*?)(?="))~"), boost::regex::JavaScript);
    boost::regex reg2(R"~((?<="appid":")(.*?)(?="}))~", boost::regex::JavaScript);
    boost::smatch rand_token_matches;
    boost::smatch appid_matches;
    if (!boost::regex_search(*resp_text, rand_token_matches, reg1)) {
        throw runtime_error("regular expression matched None : rand_token\n"+ *resp_text);
    }
    if (!boost::regex_search(*resp_text, appid_matches, reg2)) {
        throw runtime_error("regular expression matched None : appid\n"+ *resp_text);
    }
    string appid = appid_matches.str();
    string rand_token = rand_token_matches.str();
    map<const string, const string> params2 = {
            {string("appid"),      appid},
            {string("return_url"), string("https://jwgl.ustb.edu.cn/glht/Logon.do?method=weCharLogin")},
            {string("rand_token"), rand_token},
            {string("embed_flag"), string("1")}
    };
    resp_text = session.get(url2, params2).text();
    cout << *resp_text << endl;
    boost::regex reg3(R"~((?<=^\ssid = ")\w*(?=",))~", boost::regex::JavaScript);
    boost::smatch sid_matches;
    if (!boost::regex_search(*resp_text, sid_matches, reg3)) {
        throw runtime_error("regular expression matched None : sid");
    }
    string sid = sid_matches.str();
    map<const string, const string> params3 = {
            {string("sid"), sid}
    };
    cout << sid << endl;
    session.get(url3, params3).writeFile("qrcode.png");

    QPixmap img("qrcode.png");
    ui.label->setPixmap(img.scaled(ui.label->width(), ui.label->height()));
    worker->moveToThread(&thread);
    thread.start();
    emit operate(&session, sid, appid, rand_token);

}

void Window::selectCourse() {
    WebSession::Session session;
}

Window::~Window() {
    thread.quit();
    thread.wait();
}





