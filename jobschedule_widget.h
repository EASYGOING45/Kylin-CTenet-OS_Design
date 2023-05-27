#ifndef JOBSCHEDULE_WIDGET_H
#define JOBSCHEDULE_WIDGET_H

#include <QWidget>
#include"jobschedule.h"

namespace Ui {
class jobschedule_widget;
}

class jobschedule_widget : public QWidget
{
    Q_OBJECT

public:
    explicit jobschedule_widget(QWidget *parent = nullptr);
    ~jobschedule_widget();

    void displayJobs();
    void FCFS();        //先来先服务算法
    void SF();          //短作业优先算法
    void HRN();         //最高响应比优先算法

private slots:
    void on_addJobBtn_clicked();

    void on_addRandBtn_clicked();

    void on_clearBtn_clicked();

    void on_FCFS_Btn_clicked();

    void on_SF_Btn_clicked();

    void on_HRN_Btn_clicked();

private:
    Ui::jobschedule_widget *ui;
};

#endif // JOBSCHEDULE_WIDGET_H
