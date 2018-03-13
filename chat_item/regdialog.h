#ifndef REGDIALOG_H
#define REGDIALOG_H

#include <QDialog>
#include<QTcpSocket>

namespace Ui {
    class regDialog;
}

class regDialog : public QDialog
{
    Q_OBJECT

public:
    explicit regDialog(QWidget *parent = 0);
    ~regDialog();
    void showEvent(QShowEvent * event );
    int flag;
    int pflag;
private:
    Ui::regDialog *ui;
    QTcpSocket sock;

private slots:
    void on_backb_clicked();
    void on_regb_clicked();
    void onSockReadyRead();
    void onfoces();
    void onnamefoces();
};

#endif // REGDIALOG_H
