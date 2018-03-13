#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include<QString>
#include<QTcpSocket>
#include<QPushButton>
#include"friendlistdialog.h"
#include<QList>


namespace Ui {
    class chatDialog;
}

class chatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit chatDialog(QWidget *parent = 0);
    ~chatDialog();
    QString user;
    QTcpSocket *sock;
    void showEvent(QShowEvent * event );
    QPushButton *actionbutton;
    void closeEvent(QCloseEvent *event);
    friendlistDialog *fdialog;
    QStringList str;
    QList<chatDialog*>chatlist;
    QString dialogname;
    void showchatmsg(QString chatmsg);
    QString textmsg;
private:
    Ui::chatDialog *ui;
signals:
    //void rshow();
private slots:
    void on_delete_2_clicked();
    void on_send_clicked();
};

#endif // CHATDIALOG_H
