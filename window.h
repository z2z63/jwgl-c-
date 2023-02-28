

#ifndef UNTITLED_WINDOW_H
#define UNTITLED_WINDOW_H

#include <QWidget>
#include <QPushButton>
#include "ui_window.h"
#include <map>
#include <QThread>
#include "holdTcp.h"
#include <QString>

class Window : public QMainWindow {
Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

    ~Window() override;

    void showQrcode();

    void login();

    void selectCourse();

signals:

    void operate(const string &);

public slots:

    void handleResults(CURL *curl, const string sid, const string appid, const string rand_token);

private:
    Ui::MainWindow ui{};
    QThread thread{};
    holdTcp worker{};
};

#endif //UNTITLED_WINDOW_H
