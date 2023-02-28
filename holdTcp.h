#ifndef UNTITLED_HOLDTCP_H
#define UNTITLED_HOLDTCP_H

#include "session.h"
#include <QThread>
#include <curl/curl.h>
#include <QString>
#include <fstream>

class holdTcp : public QObject {
Q_OBJECT
public slots:

    void HoldTcpAndLogin();

signals:

    void resultReady(CURL *curl, const string sid, const string appid, const string rand_token);

};


#endif //UNTITLED_HOLDTCP_H
