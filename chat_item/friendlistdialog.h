#ifndef FRIENDLISTDIALOG_H
#define FRIENDLISTDIALOG_H

#include <QDialog>
#include<QTcpSocket>
#include <QTimer>
#include"groupchatdialog.h"


#define PERSON_MAX 100
namespace Ui {
    class friendlistDialog;
}

class friendlistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit friendlistDialog(QWidget *parent = 0);
    ~friendlistDialog();
     QTcpSocket *sock;
     QString username;
     virtual void showEvent(QShowEvent * event );
     QTimer ti;
     QPushButton *button[100];
     void closeEvent(QCloseEvent *event);
     QAction *m_actionmsg;
     QAction *m_actionfile;
     QStringList msgnamelist;
     groupchatDialog * groupw;
   //  QStringList strlist;
     char hmsdata[100];
     void teshow();
private:
    Ui::friendlistDialog *ui;

public slots:
     void n_time();
     void onSockReadyRead();
     void onbutton();
private slots:
    void on_group_clicked();
    void on_tabWidget_currentChanged(int index);
    void actionmsgSlot();
    void actionfileSlot();
    void ondialogclose();
    //void onrshow();
};

#endif // FRIENDLISTDIALOG_H
