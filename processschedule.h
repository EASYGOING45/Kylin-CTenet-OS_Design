#ifndef PROCESSSCHEDULE_H
#define PROCESSSCHEDULE_H
#define NUM_OF_PROCESS 6 // 系统道数
#define TIMESLICE 3      // RR调度算法时间片

#include <QWidget>            // 窗口类
#include <QDebug>             // 调试
#include <QTimer>             // 定时器
#include <QListWidgetItem>    // 列表控件
#include <QStandardItemModel> // 标准模型
#include "addprocess.h"       // 添加进程
#include "processitem.h"      // 进程条目
#include "pcb.h"              // 进程控制块
#include "choosealgo.h"       // 选择算法

namespace Ui
{
    class ProcessSchedule;
}

class ProcessSchedule : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessSchedule(QWidget *parent = nullptr);
    ~ProcessSchedule();

    // 初始化函数
    void initReadyArray();   // 初始化就绪队列
    void initBackupArray();  // 初始化后备队列
    void initSuspendArray(); // 阻塞队列

    void delFirstOfBackup(); // 删除后备队列的第一条数据
    void delFirstOfReady();  // 删除就绪队列的第一条数据
    void delOneOfReady(QString PID);
    void delOneOfSuspend(QString PID);

    void firstOfBackToReady(); // 将后备队列的第一条数据加入到就绪队列

    void workToSuspend(PCB pcb);
    void suspendToReady(PCB pcb);

    void runningToReady();        // 将运行中的进程重新加入就绪队列（进程被抢占）
    void bubbleSort_priority(PCB array[]); // 给数组排序
    void bubbleSort_runtime(PCB array[]);

    void readyToUi();   // 更新就绪队列的UI
    void backupToUi();  // 更新后备队列的UI
    void runningToUi(); // 更新运行进程的UI
    void suspendToUi(); // 更新阻塞进程的UI

    void firstOfReadyToRunningUi(); // 将就绪队列的第一条数据加入到运行进程的UI界面
    void finishToInfo();            // 将已完成的进程加入到调度信息界面

private slots:
    void receiveSF();                                                        // 短作业优先
    void receiveRR();                                                        // 时间片轮转
    void receiveHPF();                                                       // 高优先级优先
    void refreshProcs_SF();                                                  // 短作业优先算法计时槽函数
    void refreshProcs_RR();                                                  // 时间片轮转算法计时槽函数
    void refreshProcs_HPF();                                                 // 高优先级先算法计时槽函数
    void receiveSuspendToReady(QString);                                     // 解除阻塞进程的槽函数
    void receiveReadyToSuspend(QString);                                     // 阻塞进程的槽函数（就绪进程）
    void receiveRunningToSuspend(QString);                                   // 阻塞进程的槽函数（运行进程）
    void receivePCB(QString PID, QString status, int priority, int runtime); // 添加进程的槽函数

    void on_btn_choose_clicked();

    void on_btn_start_clicked();

    void on_btn_pause_clicked();

    void on_btn_continue_clicked();

    void on_btn_addProcess_clicked();

    void on_btn_reset_clicked();

signals:
    void sendWorkToSuspend(); // 发送被阻塞的就绪进程

private:
    Ui::ProcessSchedule *ui;

    int type;
    QStandardItemModel *model;
    AddProcess *addProcess;
    chooseAlgo *chooseAlgo;
    PCB ready[NUM_OF_PROCESS];
    PCB backup[100];
    PCB suspend[NUM_OF_PROCESS];
    PCB *runningProcs;
    int backupNum;
    int processNum;

    int priority_run;
    int priority_ready1st;
    int sliceTime;

    QTimer *myTimer_SF;
    QTimer *myTimer_RR;
    QTimer *myTimer_HPF;
};

#endif // PROCESSSCHEDULE_H
