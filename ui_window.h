/********************************************************************************
** Form generated from reading UI file 'windowZuAZjp.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef WINDOWZUAZJP_H
#define WINDOWZUAZJP_H

#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableWidget *course_table;
    QPlainTextEdit *console;
    QLabel *label;
    QWebEngineView *podium_webview;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1100, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        course_table = new QTableWidget(centralwidget);
        if (course_table->columnCount() < 1)
            course_table->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        course_table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        course_table->setObjectName(QString::fromUtf8("course_table"));
        course_table->setGeometry(QRect(0, 0, 300, 500));
        course_table->horizontalHeader()->setDefaultSectionSize(300);
        console = new QPlainTextEdit(centralwidget);
        console->setObjectName(QString::fromUtf8("console"));
        console->setGeometry(QRect(300, 400, 800, 400));
        console->setReadOnly(true);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 500, 300, 300));
        podium_webview = new QWebEngineView(centralwidget);
        podium_webview->setObjectName(QString::fromUtf8("podium_webview"));
        podium_webview->setEnabled(true);
        podium_webview->setGeometry(QRect(300, 0, 800, 400));
        podium_webview->setBaseSize(QSize(0, 0));
        podium_webview->setUrl(QUrl(QString::fromUtf8("about:blank")));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1100, 28));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        QTableWidgetItem *___qtablewidgetitem = course_table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\350\257\276\347\250\213\345\220\215\347\247\260", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // WINDOWZUAZJP_H
