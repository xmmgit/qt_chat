#ifndef GROUPCHATDIALOG_H
#define GROUPCHATDIALOG_H

#include <QDialog>
#include<QTcpSocket>


namespace Ui {
    class groupchatDialog;
}

class groupchatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit groupchatDialog(QWidget *parent = 0);
    ~groupchatDialog();
    QTcpSocket *sock;
    void closeEvent(QCloseEvent *event);
    void showtext(QString msg);
    void showEvent(QShowEvent * event );
    QPushButton *pb;
private:
    Ui::groupchatDialog *ui;
signals:
     void dialogclose();
private slots:
    void on_frlush_clicked();
    void on_close_clicked();
    void on_send_clicked();
};

#endif // GROUPCHATDIALOG_H
