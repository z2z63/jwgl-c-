

#ifndef UNTITLED_WINDOW_H
#define UNTITLED_WINDOW_H

#include <QWidget>
#include <QPushButton>
#include "ui_window.h"
#include <map>

class Window : public QMainWindow {
Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
//private slots:
//    void onTableClicked();
private:
    Ui::MainWindow ui{};

    void showQrcode();

    void login();
};

#endif //UNTITLED_WINDOW_H

void url_encode(char *dest, const char *origin, std::map<const char *, const char *> params);
size_t ret_recv_data(void *ptr, size_t size, size_t nmemb, void *stream);