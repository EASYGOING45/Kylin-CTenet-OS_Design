#ifndef PROCESSITEM_H
#define PROCESSITEM_H

#include <QWidget>
#include<QStandardItemModel>

namespace Ui {
class ProcessItem;
}

class ProcessItem : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessItem(QWidget *parent = nullptr);
    ~ProcessItem();
    Ui::ProcessItem *ui;

    void setModel(QStandardItemModel *model);
    void setSuspendPID(QString PID);    //设置阻塞进程

    QString getSuspendPID();
signals:
    void sendWorkToSuspend(QString);    //阻塞进程
    void sendSuspendToReady(QString);   //解除阻塞

private slots:
    void on_btn_suspend_clicked();  //槽函数

    void on_btn_unsuspend_clicked(); //槽函数

private:
    QStandardItemModel *model;
    QString PID;

};

#endif // PROCESSITEM_H
