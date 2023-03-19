#include "window.h"
#include <QWidget>
#include <boost/regex.hpp>
#include <iostream>
#include "session.h"
#include "holdTcp.h"
//#include "libxml2/libxml/xpath.h"
//#include "libxml2/libxml/parser.h"
//#include "libxml2/libxml/tree.h"

Window::Window(QWidget *parent) : QMainWindow(parent) {
    worker = new holdTcp();
    ui.setupUi(this);
//    ofstream f;
//    f.open("cookies.txt", ofstream::out | std::ofstream::trunc);
//    f.close();
    connect(this, &Window::operate, worker, &holdTcp::HoldTcpAndLogin);
    connect(&thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(worker, &holdTcp::resultReady, this, &Window::selectCourse);
    login();
}

void Window::login() {
    ifstream f;
    f.open("cookies.txt");
    if (f.good() && testCookie()) {
        return selectCourse();
    } else {
        return showQrcode();
    }

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
        throw runtime_error("regular expression matched None : rand_token\n" + *resp_text);
    }
    if (!boost::regex_search(*resp_text, appid_matches, reg2)) {
        throw runtime_error("regular expression matched None : appid\n" + *resp_text);
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
//    cout << *resp_text << endl;
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
    session.saveCookies();
    QPixmap img("qrcode.png");
    ui.label->setPixmap(img.scaled(ui.label->width(), ui.label->height()));
    worker->moveToThread(&thread);
    thread.start();
    emit operate(sid, appid, rand_token);

}

void Window::selectCourse() {
    WebSession::Session session;
    string url1 = "https://jwgl.ustb.edu.cn/xsxk/xsxkzx_index";
    string url2 = "https://jwgl.ustb.edu.cn/xsxk/xsxkzx_zy";
    string *resp_text = session.get(url1).text();
    boost::regex reg1(R"~((?<= onclick="jrxk\(')(\w*)(?='\);"))~", boost::regex::JavaScript);
    boost::smatch course_round_matches;
    if (!boost::regex_search(*resp_text, course_round_matches, reg1)) {
        throw runtime_error("regular expression matched None : course_round\n" + *resp_text);
    }
    map<const string, const string> params2 = {
            {string("jx0502zbid"), course_round_matches.str()},
    };
    resp_text = session.get(url2, params2).text();
//    cout << *resp_text << endl;
    boost::regex reg2(R"~((?<=<a href=")(.*?)(?=" target="mainFrame">必修课))~", boost::regex::JavaScript);
    boost::smatch href_matches;
    if (!boost::regex_search(*resp_text, href_matches, reg2)) {
        throw runtime_error("regular expression matched None : href\n" + *resp_text);
    }
    string url3 = "https://jwgl.ustb.edu.cn" + href_matches.str();
    resp_text = session.get(url3).text();
    cout << *resp_text << endl;
//    xmlDocPtr doc = xmlParseDoc(BAD_CAST resp_text->c_str());
//    auto *xpath = BAD_CAST "//table/tr";
//    xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, xmlXPathNewContext(doc));
//    cout << result << endl;

}

Window::~Window() {
    thread.quit();
    thread.wait();
}

bool Window::testCookie() {
    WebSession::Session session;
    string url = "https://jwgl.ustb.edu.cn/xsxk/xsxkzx_index";
    string *resp_text = session.get(url).text();
    hash<string> hasher;
    return hasher(*resp_text) != (size_t) 11966527881443034835U;
}





