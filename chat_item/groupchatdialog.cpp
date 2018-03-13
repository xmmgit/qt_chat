#include "groupchatdialog.h"
#include "ui_groupchatdialog.h"
groupchatDialog::groupchatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::groupchatDialog)
{
    ui->setupUi(this);
}


groupchatDialog::~groupchatDialog()
{
    delete ui;
}
void groupchatDialog::showEvent(QShowEvent * event )
{

        QStringList Header;
        Header<<QString::fromUtf8("名字")<<QString::fromUtf8("IP"); //表头
        ui->tableWidget->setHorizontalHeaderLabels(Header);

}
//发送按钮
void groupchatDialog::on_send_clicked()
{
    QString msg;
    msg=QString("all:")+ui->sendtext->toPlainText();
    sock->write(msg.toUtf8());
}
void groupchatDialog::on_close_clicked()
{
    close();
}

void groupchatDialog::on_frlush_clicked()
{

}
//关闭事件
void groupchatDialog::closeEvent(QCloseEvent *event)
{
    QString wclose("close:");
    sock->write(wclose.toUtf8());
    emit dialogclose();
    sock->flush();
    delete this;

}
//显示事件
void groupchatDialog::showtext(QString msg)
{
    QString record;
    record=ui->recoder->toPlainText()+QString("\n")+msg;
    ui->recoder->appendPlainText(msg);
    //ui->recoder->setPlainText(record);
    ui->sendtext->setPlainText(" ");
}
