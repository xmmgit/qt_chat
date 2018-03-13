#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include<QTcpSocket>


namespace Ui {
    class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
     void closeEvent(QCloseEvent *event);
private:
    Ui::LoginDialog *ui;
    QTcpSocket *sock;

private slots:
    void on_zaccount_clicked();
    void on_login_clicked();
    void n_confind();
    void n_Read();
};

#endif // LOGINDIALOG_H
