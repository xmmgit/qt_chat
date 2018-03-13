#include "friendlistdialog.h"
#include "ui_friendlistdialog.h"
#include"chatdialog.h"
#include<time.h>
#include <QWidget>
#include<QShowEvent>
#include <QAction>
#include<QPushButton>
#include<QList>
#include<QFile>
#include<QFileDialog>




QList<chatDialog*>pchatlist;
QList<QString>msglist;

friendlistDialog::friendlistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::friendlistDialog)
{
    ui->setupUi(this);
    //设置窗口大小
    friendlistDialog::setFixedSize(190,428);
    friendlistDialog::setWindowFlags(Qt::WindowMinMaxButtonsHint);

    //获取初显时间
    char ymddata[100];
    char hmsdata[100];
    time_t t;
    time(&t);
    struct tm *s=localtime(&t);
    sprintf(ymddata,"%d.%d.%d",s->tm_year+1900,s->tm_mon+1,s->tm_yday+1);
    sprintf(hmsdata,"%d:%d:%d",s->tm_hour,s->tm_min,s->tm_sec);
    ui->ymdtime->setText(QString::fromUtf8(ymddata));
    ui->yfmtime->setText(QString::fromUtf8(hmsdata));
    connect(&ti,SIGNAL(timeout()),this,SLOT(n_time()));
    ti.start(1000);
}

friendlistDialog::~friendlistDialog()
{
    delete ui;
}
//显示事件：显示当前用户
void friendlistDialog::showEvent(QShowEvent * event )
{

    if(event->type()==QEvent::Show)
    {
        //QPushButton *mchat=new QPushButton(QString::fromUtf8("+加入群聊"),ui->tab_2);
        //mchat->setFixedSize(165,30);
        ui->name->setText(QString::fromUtf8(username.toUtf8()));
    }
}
//显示时间
void friendlistDialog::n_time()
{
    char ymddata[100];
    char hmsdata[100];
    time_t t;
    time(&t);
    struct tm *s=localtime(&t);
    sprintf(ymddata,"%d.%d.%d",s->tm_year+1900,s->tm_mon+1,s->tm_yday+1);
    sprintf(hmsdata,"%d:%d:%d",s->tm_hour,s->tm_min,s->tm_sec);
    ui->ymdtime->setText(QString::fromUtf8(ymddata));
    ui->yfmtime->setText(QString::fromUtf8(hmsdata));
}
//读取服务器发送过来的信息，并创建好友列表
void friendlistDialog::onSockReadyRead()
{

    static int i=0;
    int j=0;
    static int by=0;
    QString usertext=QString::fromUtf8(sock->readAll().data());
    usertext.trimmed();
    QStringList strlist=usertext.split(":");
    QString msg;
    //时间
    char hmsdata[100];
    time_t t;
    time(&t);
    struct tm *s=localtime(&t);
    sprintf(hmsdata,"%d:%d:%d",s->tm_hour,s->tm_min,s->tm_sec);
    //创建对象按钮
    if((strlist.at(0)==QString("button")))
    {
           msg=strlist.at(2)+QString(":")+strlist.at(3)+QString(":")+strlist.at(1);
           for(;j<i;j++)
           {
                if(button[j]->text()==msg)
                    break;
           }
           if(j==i)
           {
               button[i]=new QPushButton(msg,ui->widget);
               button[i]->setFixedSize(165,20);
               button[i]->move(0,by);
               //button[i]->setStyleSheet("background-color:rgb(0,244,0)");
               by+=20;
               button[i]->show();
               connect(button[i],SIGNAL(clicked()),this, SLOT(onbutton()));
               /****************************************menu*************************/
               setContextMenuPolicy(Qt::ActionsContextMenu);

                   m_actionmsg= new QAction(button[i]);
                   m_actionfile= new QAction(button[i]);

                   m_actionmsg->setText(QString::fromUtf8("发送消息"));
                   m_actionfile->setText(QString::fromUtf8("发送文件"));

                   addAction(m_actionmsg);
                   addAction(m_actionfile);

                   connect(m_actionmsg, SIGNAL(triggered()), this, SLOT(actionmsgSlot()));
                   connect(m_actionfile, SIGNAL(triggered()), this, SLOT(actionfileSlot()));
               /*****************************************end*************************/
               i++;
               if(i>PERSON_MAX)
                exit(-1);
         }
    }
    //接收文件
    if(strlist.at(0)==QString("file"))
    {

    }
    //接收群消息
    if(strlist.at(0)==QString("all"))
    {
        QString alltext;
        alltext=strlist.at(1)+QString("--")+QString(hmsdata)+QString("\n")+strlist.at(2);
        groupw->showtext(alltext);

    }
    /********************************************start************************************/
     //显示消息
     chatDialog *pc;
     foreach(pc,pchatlist)
     if((pc->dialogname==strlist.at(0))&&pc!=NULL)
     {
         qDebug()<<pc->dialogname;
         qDebug()<<pchatlist.size();
         qDebug()<<strlist.at(0);
         QString msgshow=QString("\n")+strlist.at(0)+QString("--")+QString(hmsdata)+QString("\n")+strlist.at(2);
         pc->showchatmsg(msgshow);
         return;
     }


     QString text=strlist.at(0)+QString("--")+QString(hmsdata)+QString("\n")+strlist.at(2);
     msglist.push_back(text);
    /**********************************************end***********************************/
}
void friendlistDialog::teshow()
{

}
/*
//显示信息
void friendlistDialog::onrshow()
{
    QString msgshow;
    chatDialog *pc;
    foreach(pc,pchatlist)
    if(pc->dialogname==strlist.at(0))
    {
        qDebug()<<pc->dialogname;
        qDebug()<<strlist.at(0);
        QString rmsg=QString("\n")+strlist.at(0)+QString("--")+QString(hmsdata)+QString("\n")+strlist.at(2);
        msgshow+=rmsg;
        pc->showchatmsg(msgshow);
        return;
    }
}
*/
//按钮响应槽函数
void friendlistDialog::onbutton()
{

    QString msgname;
    //QStringList msgnamelist;
    chatDialog *chat=new chatDialog;
    qDebug("%p",chat);
    chat->user=((QPushButton*)sender())->text();
    msgname=((QPushButton*)sender())->text();
    msgnamelist=msgname.split(":");
    chat->dialogname=msgnamelist.at(0);
   // qDebug("%s",chat->dialogname);
    pchatlist.append(chat);
    chat->chatlist=pchatlist;
    chat->sock=sock;
    //disconnect(sock,SIGNAL(readyRead()),this,SLOT(onSockReadyRead()));
    chat->actionbutton=((QPushButton*)sender());
    chat->fdialog=this;
    QString m;
    foreach(m,msglist)
    {
        QStringList mlist;
        mlist=m.split("--");
        if((mlist.at(0)==msgnamelist.at(0)))
        {
            chat->showchatmsg(m);
        }
    }
    chat->show();
    disconnect(((QPushButton*)sender()),SIGNAL(clicked()),this, SLOT(onbutton()));

}

void friendlistDialog::on_tabWidget_currentChanged(int index)
{

}
void friendlistDialog::closeEvent(QCloseEvent *event)
{
    QString wclose("close:");
    /*chatDialog *pc;
    foreach(pc,pchatlist)
        delete pc;
     */
    sock->write(wclose.toUtf8());
    sock->flush();
    sock->close();
    delete this;

}
void friendlistDialog::on_group_clicked()
{
    groupw=new groupchatDialog;
    groupw->sock=sock;
    groupw->pb=((QPushButton*)sender());
    groupw->show();
    disconnect(ui->group,SIGNAL(clicked()),this, SLOT(on_group_clicked()));
    connect(groupw,SIGNAL(dialogclose()),this,SLOT(ondialogclose()));
}
void friendlistDialog::ondialogclose()
{
    connect(groupw->pb,SIGNAL(clicked()),this, SLOT(on_group_clicked()));
}
//右键菜单按钮发送
void friendlistDialog::actionmsgSlot()
{
    qDebug("msg");
    //QString msgname;
    //QStringList msgnamelist;
    chatDialog *chat=new chatDialog;
   // chat->show();
    qDebug("%p",chat);
   // chat->user=((QPushButton*)sender())->text();
   // msgname=((QPushButton*)sender())->text();
   // msgnamelist=msgname.split(":");
   // chat->dialogname=msgnamelist.at(0);
   // qDebug("%s",chat->dialogname);
   // pchatlist.append(chat);
   // chat->chatlist=pchatlist;
  //  chat->sock=sock;
    //disconnect(sock,SIGNAL(readyRead()),this,SLOT(onSockReadyRead()));
    //chat->actionbutton=((QPushButton*)sender());
   // chat->fdialog=this;
    //chat->show();
    //disconnect(((QPushButton*)sender()),SIGNAL(clicked()),this, SLOT(onbutton()));
}
//传输文件
void friendlistDialog::actionfileSlot()
{
    qDebug("file");
    /*
    QString msgname;
    QString filename=QFileDialog::getOpenFileName(this,QString::fromUtf8("请选择一个文件"),"",QString::fromUtf8("文本文件(*.txt);;所有文件(*.*)"));
    if(filename=="")
        return;
    qDebug("%s",filename.toUtf8().data());
    QFile rf(filename);
    if(!rf.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"open fail";
        return;
    }
    msgname=((QPushButton*)sender())->text();
    msgnamelist=msgname.split(":");
    QString filemsg=msgnamelist.at(2)+QString(":")+QString(rf.readAll().data());
    sock->write(filemsg.toUtf8());
    */
}
