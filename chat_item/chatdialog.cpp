#include "chatdialog.h"
#include "ui_chatdialog.h"
#include<qDebug>
#include<time.h>
#include<QPalette>
#include"friendlistdialog.h"



chatDialog::chatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatDialog)
{
    ui->setupUi(this);
}

chatDialog::~chatDialog()
{
    delete ui;
}

//设置对话框主题
void chatDialog::showEvent(QShowEvent * event )
{
    if(event->type()==QEvent::Show)
    {
        //qDebug()<<user;
        //数据处理将从按钮对象上获取的信息拆分
        chatDialog::setWindowTitle(user);
        str=user.split(":");
        QString clientsock=QString("sock:")+str.at(2);
        sock->write(clientsock.toUtf8());
        // connect(this,SIGNAL(rshow()),fdialog, SLOT(onrshow()));
         //emit rshow();
    }
}
void chatDialog::on_send_clicked()
{
    //显示时间
    char hmsdata[100];
    time_t t;
    time(&t);
    struct tm *s=localtime(&t);
    sprintf(hmsdata,"%d:%d:%d",s->tm_hour,s->tm_min,s->tm_sec);
    QString text=ui->msg->toPlainText();
    //信息格式 sock:要发送的信息
    QString msg=str.at(2)+QString(":")+text;
    QString me=QString("Adminator");
    //显示自己的信息
    QString metext=QString("\n")+me+QString("--")+QString(hmsdata)+QString("\n")+text;
    ui->record->appendPlainText(metext);
    ui->msg->setPlainText(" ");
    sock->write(msg.toUtf8());
}
void chatDialog::on_delete_2_clicked()
{
    close();
}
void chatDialog::closeEvent(QCloseEvent *event)
{
    qDebug("ce");
    connect(actionbutton,SIGNAL(clicked()),fdialog, SLOT(onbutton()));
    disconnect(sock,SIGNAL(readyRead()),this,SLOT(onSockReadyRead()));
    delete this;
}
void chatDialog::showchatmsg(QString chatmsg)
{
    //textmsg.append(chatmsg);
    ui->record->appendPlainText(chatmsg);
    //qDebug()<<textmsg;
    ui->msg->setPlainText(" ");
}
