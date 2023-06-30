#ifndef JOBSCHEDULE_H
#define JOBSCHEDULE_H

#include"pcb_calculate.h"
#include<QString>

//作业调度类
class jobSchedule
{
public:
    jobSchedule();
    int getJobLength();
    void addJob(string name,int arrive,int service);
    pcb_cal *getRandomJob();        //获得一个随即作业
    bool addRandJobs();             //随机生成一个进程
    void initFlag();                //将所有作业的完成标记都重置为0
    void clear();                   //清空所有作业


    pcb_cal *jobHead;
    bool isEmpty = true;    //标记是否为为空
};

#endif // JOBSCHEDULE_H
