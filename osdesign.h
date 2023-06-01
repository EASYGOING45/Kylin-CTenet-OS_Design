#ifndef OSDESIGN_H
#define OSDESIGN_H

#include <QMainWindow>
#include<QPainter>
#include<QString>
#include<QDebug>
#include<QMessageBox>
#include<QIcon>
#include"processschedule.h"
#include"pagereplacement.h"
#include"jobschedule_widget.h"
#include"disktrack.h"
#include"processmanager.h"

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

    void on_PageReplacementBtn_clicked();

    void on_DiskScheduleBtn_clicked();

    void on_ProcessManagerBtn_clicked();

private:
    Ui::OSDesign *ui;
    jobschedule_widget page_job;    //作业调度算法模拟页面
    ProcessSchedule page_process;   //进程调度模拟页面
    PageReplacement pageReplace;    //页面调度算法模拟页面
    DiskTrack pageDisk;             //磁道调度算法模拟页面
    ProcessManager processmana;     //Windows进程管理页面
};

#endif // OSDESIGN_H
