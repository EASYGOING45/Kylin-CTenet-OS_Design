#ifndef PCB_CALCULATE_H
#define PCB_CALCULATE_H

#include<iostream>
#include<string>
using namespace std;
//该进程控制块头文件用于控制进程调度中的算数周转

//链表结构PCB
struct pcb_cal
{
    string name;    //名称
    int service;    //服务事件
    int finish;     //结束时间
    int arrive;     //到达时间
    float response; //响应比
    int turnaround; //周转时间
    float weightedturnaround;       //带权周转时间
    bool flag = 0;      //标记--是否已服务
    pcb_cal* next;
};

#endif // PCB_CALCULATE_H
