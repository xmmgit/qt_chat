#include "logindialog.h"
#include "ui_logindialog.h"
#include"friendlistdialog.h"
#include"regdialog.h"
#include"chatdialog.h"
#include<QMessageBox>
#include<QString>
#include <QLineEdit>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    sock=new QTcpSocket;
    //ui->login->setStyleSheet("border-radius:30px");

    //信号与槽函数连接
    connect(sock,SIGNAL(connected()),this,SLOT(n_confind()));
    connect(sock,SIGNAL(readyRead()),this,SLOT(n_Read()));
}

LoginDialog::~LoginDialog()
{

    delete ui;
}

void LoginDialog::on_login_clicked()
{
    //链接
    if((ui->username->text()!=NULL)&&(ui->userpassword->text()!=NULL))
    {
        sock->connectToHost("192.168.9.119",9999);
        char choicelog[20]="log";
        //发送登录识别
        sock->write(choicelog);
    }
    if(ui->username->text()==NULL)
        ui->username->setPlaceholderText(QString::fromUtf8("username not NULL"));
    if(ui->userpassword->text()==NULL)
        ui->userpassword->setPlaceholderText(QString::fromUtf8("userpassword not NULL"));
}
void LoginDialog::n_confind()
{
    qDebug("connect success");
}
//读取从服务器发过来的信息
void LoginDialog::n_Read()
{

    friendlistDialog *flist=new friendlistDialog;
    char *text=sock->readAll().data();
    if(strcmp(text,"ok")==0)
    {
        QString usermsg=QString("%1:%2\n").arg(ui->username->text()).arg(ui->userpassword->text());
        sock->write(usermsg.trimmed().toUtf8());
    }
    else if(strcmp(text,"0")==0)
    {
        flist->username=ui->username->text();
        flist->show();
        disconnect(sock,SIGNAL(connected()),this,SLOT(n_confind()));
        disconnect(sock,SIGNAL(readyRead()),this,SLOT(n_Read()));
        connect(sock,SIGNAL(readyRead()),flist,SLOT(onSockReadyRead()));
        flist->sock=sock;
         close();
    }
    else if(strcmp(text,"1")==0)
    {
        QMessageBox::warning(this,QString::fromUtf8("提示"),QString::fromUtf8("密码错误！！请重新输入"));
        sock->disconnectFromHost();
    }
    else if(strcmp(text,"2")==0)
    {
        QMessageBox::critical(this,QString::fromUtf8("提示"),QString::fromUtf8("还未注册，请先注册"));
        sock->disconnectFromHost();
    }

}

void LoginDialog::on_zaccount_clicked()
{
    regDialog *reg=new regDialog;
    reg->show();
}
void LoginDialog::closeEvent(QCloseEvent *event)
{

}
