#ifndef PCB_H
#define PCB_H
#define NUM_OF_PROCESS 6 //系统最大道数

#include<QString> //导入QString类

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
    PCB();  //默认构造函数
    PCB(QString PID,QString status,int priority,int runtime);    //构造函数，传入进程标识符、状态、优先级、已运行时间

    void setRuntime(int value); //设置进程运行时间
    void delRuntime(int value); //进程运行时间减少value
    void setStatus(QString value);  //设置进程状态
    void setPID(QString value); //设置进程标识符
    void setMaxRuntime(int value);  //设置进程所需要的总运行时间
    void setPriority(int value);    //设置进程优先级
    void delPriority(int value);    //进程优先级降低val
    void addPriority(int value);    //进程优先级增加value
    void setDefaultPCB();   //初始化进程控制块

    QString getPID() const; //获取进程标识符
    int getRuntime() const; //获取进程已运行时间
    int getMaxRuntime() const;  //获取进程需要的总运行时间
    QString getStatus() const;  //获取进程状态
    int getPriority() const;    //获取进程优先级
};

#endif // PCB_H
