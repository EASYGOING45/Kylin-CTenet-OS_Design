#ifndef PCB_H
#define PCB_H
#define NUM_OF_PROCESS 6 //系统最大道数

#include<QString>


class PCB
{
private:
    QString PID;    //进程标识符
    QString status; //进程状态
    int priority;   //进程优先级
    int runtime;    //进程已运行时间
    int max_runtime;    //进程需要的总运行时间
    PCB *pcb;   //进程控制块指针
public:
    PCB();
    PCB(QString PID,QString status,int priority,int runtime);

    void setRuntime(int value);
    void delRuntime(int value); //进程运行时间减少value
    void setStatus(QString value);
};

#endif // PCB_H
