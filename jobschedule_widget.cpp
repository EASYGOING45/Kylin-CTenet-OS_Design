#include "jobschedule_widget.h"
#include "ui_jobschedule_widget.h"
#include<QString>
#include<QMessageBox>
#include<QTime>
#include<QDebug>
#include"jobschedule.h"

jobSchedule job;        //类对象的前置声明

int aturnaround = 0;    //平均周转时间
float aweightedturnaround = 0;  //平均带权周转时间

jobschedule_widget::jobschedule_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jobschedule_widget)
{
    ui->setupUi(this);

    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
       QBrush(QPixmap(":/images/images/back3.jpg").scaled( // 缩放背景图.
       this->size(),
       Qt::IgnoreAspectRatio,
       Qt::SmoothTransformation))); // 使用平滑的缩放方式
    this->setPalette(palette); // 至此, 已给widget加上了背景图.

}

jobschedule_widget::~jobschedule_widget()
{
    delete ui;
}

void jobschedule_widget::displayJobs()
{
    ui->textBrowser->clear();
    pcb_cal *p = new pcb_cal;
    p=job.jobHead->next;

    while(p)
    {
        ui->textBrowser->append("进程名："+QString::fromStdString(p->name)+
                                " 到达时间："+QString::number(p->arrive)+
                                " 所需时间："+QString::number(p->service));
        p=p->next;
    }
}

//先来先服务算法 FCFS
void jobschedule_widget::FCFS()
{
    ui->textBrowser_2->append("FCFS:");

    int clock = 0;
    aturnaround = 0;
    aweightedturnaround = 0;

    bool non;
    for (int i = 0; i < job.getJobLength(); i++)
    {
        non = false;
        pcb_cal* p = new pcb_cal;           //用来遍历链表

        pcb_cal* q = new pcb_cal;            //q用来存放当前时刻已到达且到达时间最早的结点
        q->next=nullptr;

        p = job.jobHead->next;
        q->arrive = 1000000;         //初始值设置为最大的数
        //遍历寻找已到达且到达时间最早的结点
        while (p != NULL)
        {
            if (p->flag ==0 && p->arrive <= q->arrive && (p->arrive <= clock))
            {
                q = p;
                non = true;
            }
            p = p->next;
        }

        //若没找到，说明当前时刻没有已到达的进程
        if (!non)
        {
            q->arrive = 1000000;
            q->next = nullptr;
            p = job.jobHead->next;
            while (p != NULL)
            {
                if (p->flag== 0 && p->arrive <= q->arrive)
                {
                    q = p;
                }
                p = p->next;
            }
        }

        if(i==0) clock=q->arrive;
        if(!non) clock=q->arrive;
        clock+=q->service;
        q->finish=clock;
        q->turnaround=q->finish-q->arrive;
        aturnaround+=q->turnaround;
        q->weightedturnaround=q->turnaround/(q->service*1.0);
        aweightedturnaround+=q->weightedturnaround;
        q->flag=1;
        ui->textBrowser_2->append("进程名："+QString::fromStdString(q->name)+
                                  " 到达时间："+QString::number(q->arrive)+
                                  " 服务时间："+QString::number(q->service));

        QTime time;
        time.start();
        while(time.elapsed() < 800)             //等待时间流逝0.8秒钟
            QCoreApplication::processEvents();   //处理事件

    }
    ui->textBrowser_2->append("平均周转时间："+QString::number(aturnaround / (1.0*job.getJobLength()))+
                              "  平均带权周转时间："+QString::number(aweightedturnaround / (1.0*job.getJobLength())));
    job.initFlag();   //执行完FCFS算法后将flag标记都置为0
}

void jobschedule_widget::SF()
{
    ui->textBrowser_2->append("SF短作业优先算法:");

    int clock = 0;
    aturnaround = 0;
    aweightedturnaround = 0;
    bool non;


    for (int i = 0; i < job.getJobLength(); i++)
    {
        non = false;
        pcb_cal* p = new pcb_cal;
        p=job.jobHead->next;

        pcb_cal* q = new pcb_cal;
        q->service = 10000;
        q->next = NULL;

        while (p != NULL)
        {
            if (p->arrive <= clock)
            {
                if (p->flag == 0 && p->service <= q->service)  //选出服务时间最短的进程
                {
                    q = p;
                    non = true;
                }
            }
            p = p->next;
        }

        if (!non)  //找不到已到达的进程，则选择最早到达的进程
        {
            q->arrive =100000;
            q->next = NULL;
            p = job.jobHead->next;
            while (p != NULL)
            {
                if (p->service != 0 && p->arrive <= q->arrive)
                {
                    q = p;
                }

                p = p->next;
            }
        }
        if (i == 0) clock = q->arrive;
        if (!non) clock = q->arrive;
        clock += q->service;
        q->finish = clock;
        q->turnaround = q->finish - q->arrive;
        aturnaround += q->turnaround;
        q->weightedturnaround = q->turnaround / (q->service * 1.0);
        aweightedturnaround += q->weightedturnaround;
        q->flag = 1;  //标记为已服务

        ui->textBrowser_2->append(" 进程名："+QString::fromStdString(q->name)+
                                  " 到达时间："+QString::number(q->arrive)+
                                  " 服务时间："+QString::number(q->service));

        QTime time;
        time.start();
        while(time.elapsed() < 800)             //等待时间流逝0.8秒钟
            QCoreApplication::processEvents();   //处理事件

    }
    ui->textBrowser_2->append("平均周转时间："+QString::number(aturnaround / (1.0*job.getJobLength()))+
                              "  平均带权周转时间："+QString::number(aweightedturnaround / (1.0*job.getJobLength())));
    job.initFlag();   //执行完算法后将flag标记都置为0
}

void jobschedule_widget::HRN()
{
    ui->textBrowser_2->append("HRN最高响应比优先算法:");

    int clock = 0;
    aturnaround = 0;
    aweightedturnaround = 0;
    bool non;
    for (int i = 0; i < job.getJobLength(); i++)
    {
        non = false;
        pcb_cal* p = new pcb_cal;
        p=job.jobHead->next;

        pcb_cal* q = new pcb_cal;
        q->response = -1;
        q->next = nullptr;
        while (p != NULL)
        {
            if (p->arrive <= clock)  //如果p已到达
            {
                p->response=((clock-p->arrive)/(p->service*1.0))+1;  //更新p的响应比
                if (p->flag== 0 && p->response >= q->response)     //选出最高的响应比
                {
                    q = p;

                    non = true;
                }
            }

            p = p->next;
        }

        if (!non)  //如果没有到达的进程，则选择最早到达的一个进程
        {
            q->arrive = 10000;
            q->next = NULL;
            p = job.jobHead->next;
            while (p != NULL)
            {
                if (p->flag== 0 && p->arrive <= q->arrive)
                {
                    q = p;
                }

                p = p->next;
            }
        }

        if (i == 0) clock = q->arrive;
        if (!non) clock = q->arrive;
        clock += q->service;
        q->finish = clock;
        q->turnaround = q->finish - q->arrive;
        aturnaround += q->turnaround;
        q->weightedturnaround = q->turnaround / (q->service * 1.0);
        aweightedturnaround += q->weightedturnaround;
        q->flag=1;  //将q标记为已服务
        ui->textBrowser_2->append(" 进程名："+QString::fromStdString(q->name)+
                                  " 到达时间："+QString::number(q->arrive)+
                                  " 服务时间："+QString::number(q->service));

        QTime time;
        time.start();
        while(time.elapsed() < 800)             //等待时间流逝0.8秒钟
            QCoreApplication::processEvents();   //处理事件

    }
    ui->textBrowser_2->append("平均周转时间："+QString::number(aturnaround / (1.0*job.getJobLength()))+
                              "  平均带权周转时间："+QString::number(aweightedturnaround / (1.0*job.getJobLength())));
    job.initFlag();   //执行完后将fla    eg标记都置为0
}


void jobschedule_widget::on_addJobBtn_clicked()
{
    qDebug()<<"点击添加按钮---------------";
    //添加作业
    QString QName = ui->lineName->text();
    QString QArrive = ui->lineArrive->text();
    QString QService = ui->lineNeed->text();
    if(QName !="" && QService != "")
    {
        job.addJob(QName.toStdString(),QArrive.toInt(),QService.toInt());
        QMessageBox::information(this,"提示","添加成功");
        displayJobs();
    }
    else

    {
        QMessageBox::information(this,"提示","作业名和服务时间不能为空");
    }
}

void jobschedule_widget::on_addRandBtn_clicked()
{
    job.addRandJobs();
    QMessageBox::information(this,"提示：","已随机添加五个进程");
    displayJobs();
}

void jobschedule_widget::on_clearBtn_clicked()
{
    job.clear();
    displayJobs();
}

void jobschedule_widget::on_FCFS_Btn_clicked()
{
    FCFS();
}

void jobschedule_widget::on_SF_Btn_clicked()
{
    SF();
}

void jobschedule_widget::on_HRN_Btn_clicked()
{
    HRN();
}

