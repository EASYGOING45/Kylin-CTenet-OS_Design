#include "jobschedule.h"
#include<QDateTime>
#include<QDebug>
#include<QString>

jobSchedule::jobSchedule()
{
    //执行初始化操作
    this->jobHead = new pcb_cal;
    jobHead->next = nullptr;
    this->isEmpty=true;
}


int jobSchedule::getJobLength()
{
    //获取作业信息  总的作业个数
    pcb_cal* p = new pcb_cal;
    p->next = nullptr;
    p=jobHead->next;
    int n = 0;

    while(p)
    {
        //遍历链表
        n++;
        p=p->next;
    }
    return n;
}

//添加一个进程
void jobSchedule::addJob(string name, int arrive, int service)
{
    if(isEmpty)
    {
        pcb_cal *newNode=new pcb_cal;
        newNode->next=nullptr;
        newNode->name=name;
        newNode->arrive=arrive;
        newNode->service=service;
        qDebug()<<"创建新进程成功，此时处于isEmpty=true的逻辑判断语句中";
        this->jobHead->next=newNode;
        this->isEmpty=false;
    }
    else
    {
        pcb_cal *p=new pcb_cal;
        p=jobHead->next;        //首元节点
        if(p==nullptr)
        {
            qDebug()<<"p是nullptr";
        }
        while(p->next)
        {
            p=p->next;      //直至找到尾节点
        }

        qDebug()<<"开始创建新进程q";
        pcb_cal *q = new pcb_cal;
        q->next=nullptr;
        q->name=name;
        q->arrive=arrive;
        q->service=service;
        if(q->service==service)
        {
            qDebug()<<"创建新进程q成功";
        }

        //尾插法
        q->next = p->next;
        p->next=q;
    }
}

//随机获取一个进程
pcb_cal *jobSchedule::getRandomJob()
{
    qsrand(QDateTime::currentMSecsSinceEpoch());        //为随机值设定一个seed

    const char chrs[] = "abcdefghijklmnopqrstuvwxyz";
    int chrs_size = sizeof(chrs);
    int randomx = 0;

    randomx = rand() % (chrs_size-1);
    char ch = chrs[randomx];

    QString Qstr(ch);

    pcb_cal *p=new pcb_cal;
    p->next = nullptr;
    p->name=Qstr.toStdString(); //取随机生成的字母作为进程名

    //检测是否存在同名的进程名，若存在则返回空指针
    pcb_cal *q=new pcb_cal;
    q=jobHead->next;
    while(q)
    {
        if(q->name==Qstr.toStdString())
        {
            return nullptr;
        }
        q=q->next;
    }
    delete q;

    p->arrive = rand() % 100;   //取0到100的随机数作为进程到达时间
    p->service = rand() % 99 +1;    //取1到100的随机数作为进程服务时间
    return p;
}

//随机添加五个进程
bool jobSchedule::addRandJobs()
{
    int i= 1;
    while(i<=5)
    {
        pcb_cal *q=new pcb_cal;
        q->next = nullptr;
        q=getRandomJob();
        if(q!=nullptr)
        {
            q->next = jobHead->next;
            jobHead->next = q;      //头插
            i++;
        }
        q=nullptr;
        delete q;
    }

}

void jobSchedule::initFlag()
{
    pcb_cal *p=new pcb_cal;
    p=jobHead->next;
    while(p)
    {
        p->flag=0;
        p=p->next;
    }
}

void jobSchedule::clear()
{
    pcb_cal *p=jobHead->next;
    pcb_cal *q;
    while(p!=nullptr)
    {
        q=p->next;
        delete p;
        p=q;
    }
    jobHead->next = nullptr;
}



