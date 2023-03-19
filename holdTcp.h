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

    void HoldTcpAndLogin(const string sid, const string appid, const string rand_token);

signals:

    void resultReady();

};


#endif //UNTITLED_HOLDTCP_H
