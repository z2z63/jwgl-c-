#ifndef UNTITLED_HOLDTCP_H
#define UNTITLED_HOLDTCP_H
#include "session.h"
#include <QThread>
#include <curl/curl.h>
class holdTcp {
    Q_OBJECT
public:
    void HoldTcpAndLogin(CURL* curl, string appid, string rand_token, string sid);
};


#endif //UNTITLED_HOLDTCP_H
