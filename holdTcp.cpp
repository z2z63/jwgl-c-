
#include "holdTcp.h"
#include <boost/regex.hpp>

void
holdTcp::HoldTcpAndLogin(const string sid, const string appid, const string rand_token) {
    auto session = new WebSession::Session();
    curl_easy_setopt(session->curl, CURLOPT_COOKIEFILE, "cookies.txt");
    curl_easy_setopt(session->curl, CURLOPT_COOKIEJAR, "cookies.txt");
    string *resp_text = nullptr;
    string url4 = "https://sis.ustb.edu.cn/connect/state";
    string url5 = "https://jwgl.ustb.edu.cn/glht/Logon.do";
    map<const string, const string> params4 = {
            {string("sid"), sid}
    };
    resp_text = session->get(url4, params4).text();
    cout << *resp_text << endl;
    resp_text = session->get(url4, params4).text();
    cout << *resp_text << endl;
    boost::regex reg(R"~((?<="data":")(.*?)(?="}))~", boost::regex::JavaScript);
    boost::smatch auth_code_matches;
    if (!boost::regex_search(*resp_text, auth_code_matches, reg)) {
        throw runtime_error("regular expression matched None : appid\n" + *resp_text);
    }
    string auth_code = auth_code_matches.str();
    cout << auth_code << endl;
    map<const string, const string> params5 = {
            {string("method"),     string("weCharLogin")},
            {string("appid"),      appid},
            {string("auth_code"),  auth_code},
            {string("rand_token"), rand_token}
    };
    resp_text = session->get(url5, params5).text();
    cout << *resp_text << endl;
    delete session;
    emit resultReady();
}



