#include "regdialog.h"
#include "ui_regdialog.h"
#include<QShowEvent>
#include<QMessageBox>
#include <QObject>
regDialog::regDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regDialog)
{
    ui->setupUi(this);
}

regDialog::~regDialog()
{
    delete ui;
}

void regDialog::showEvent(QShowEvent * event )
{

    if(event->type()==QEvent::Show)
    {
        sock.connectToHost("192.168.9.119",9999);
        char choicelog[20]="reg";
        //发送登录识别
        sock.write(choicelog);
        ui->regb->setEnabled(false);
    }
    connect(&sock,SIGNAL(readyRead()),this,SLOT(onSockReadyRead()));
    connect(ui->rpassword,SIGNAL(editingFinished()),this,SLOT(onfoces()));
    connect(ui->name,SIGNAL(editingFinished()),this,SLOT(onnamefoces()));
}
void regDialog::on_regb_clicked()
{
    int nsex;
    QString sex;
    QString name=ui->name->text();
    QString password=ui->password->text();
    QString rpassword=ui->rpassword->text();
    nsex=ui->mb->isChecked();
    if(nsex==1)
    {
        sex=QString::fromUtf8("男");
    }
    else
    {
        sex=QString::fromUtf8("女");
    }
    QString bir=ui->bir->text();
    QString mail=ui->mail->text();
    QString addr=ui->addr->text();
    QString usermsg=name+QString(":")+password+QString(":")+rpassword+QString(":")+sex+QString(":")+bir+QString(":")+mail+
                    QString(":")+addr;

    sock.write(usermsg.toUtf8());
}

void regDialog::on_backb_clicked()
{
    close();
}
void regDialog::onSockReadyRead()
{
    QString reply(sock.readAll().data());
    qDebug()<<reply;
    if(reply=="yes")
    {
        QPalette npa;
        npa.setColor(QPalette::WindowText,Qt::red);
        ui->nametip->setPalette(npa);
        QPalette gpa;
        gpa.setColor(QPalette::WindowText,Qt::green);
        ui->nametip->setPalette(gpa);
        if(ui->name->text()=="")
        {
           ui->nametip->setText(QString::fromUtf8("昵称NULL！！！"));
           ui->regb->setEnabled(false);
           ui->nametip->setPalette(npa);
        }
        else
        {
            ui->nametip->setText(QString::fromUtf8("昵称可用"));
                    flag=1;
            if(pflag==1)
                 ui->regb->setEnabled(true);
        }
    }
    else if(reply=="no")
    {
        ui->nametip->setText(QString::fromUtf8("昵称已存在！！！"));
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::red);
        ui->nametip->setPalette(pa);
        ui->regb->setEnabled(false);
        flag=0;
    }
    else if(reply=="0")
    {
        QMessageBox::information(this,QString::fromUtf8("提示"),QString::fromUtf8("注册成功"));
        ui->regb->setEnabled(false);
    }
    else if(reply=="1")
    {
        QMessageBox::critical(this,QString::fromUtf8("提示"),QString::fromUtf8("注册失败！！"));
    }
}
void regDialog::onnamefoces()
{
     QString name=QString("name:")+ui->name->text();
     sock.write(name.toUtf8());
}
void regDialog::onfoces()
{

        if(ui->password->text()!=ui->rpassword->text())
        {
            ui->rpastip->setText(QString::fromUtf8("两次密码不一致"));
            QPalette pa;
            pa.setColor(QPalette::WindowText,Qt::red);
            ui->rpastip->setPalette(pa);
            ui->regb->setEnabled(false);
            pflag=0;
        }
        else
        {
            if((ui->password->text()!=""))
            {

                ui->rpastip->setText(QString::fromUtf8("密码可用"));
                QPalette pa;
                pa.setColor(QPalette::WindowText,Qt::green);
                ui->rpastip->setPalette(pa);
                if(flag==1)
                {
                    ui->regb->setEnabled(true);
                }
                pflag=1;
            }
        }
}
