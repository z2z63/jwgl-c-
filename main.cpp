#include <QApplication>
#include "window.h"

int main(int argc, char **argv) {
    qRegisterMetaType<string>("string");
    QApplication app(argc, argv);
    auto w = Window();
    w.show();
    return QApplication::exec();
}