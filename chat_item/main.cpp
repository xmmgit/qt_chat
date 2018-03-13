#include <QtGui/QApplication>
#include "logindialog.h"
#include<QTextCodec>
#include<QApplication>
#include <QWidget>
#include<QIcon>
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    LoginDialog w;
    w.setFixedSize(419,316);
    w.setWindowFlags(Qt::WindowMinMaxButtonsHint);
    //a.setWindowIcon(QIcon("3.ico"));
    w.show();

    return a.exec();
}
