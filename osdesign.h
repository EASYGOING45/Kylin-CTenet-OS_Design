#ifndef OSDESIGN_H
#define OSDESIGN_H

#include <QMainWindow>
#include<QPainter>
#include<QString>
#include<QDebug>
#include<QMessageBox>
#include<QIcon>
#include"jobschedule_widget.h"
#include"processschedule.h"


namespace Ui {
class OSDesign;
}

class OSDesign : public QMainWindow
{
    Q_OBJECT

public:
    explicit OSDesign(QWidget *parent = nullptr);
    ~OSDesign();

private slots:
    void on_ProcessScheduleBtn_clicked();

    void on_JobScheduleBtn_clicked();

private:
    Ui::OSDesign *ui;
    jobschedule_widget page_job;    //作业调度算法模拟页面
    ProcessSchedule page_process;   //进程调度模拟页面
};

#endif // OSDESIGN_H
