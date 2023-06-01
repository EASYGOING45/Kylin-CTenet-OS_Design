#include "osdesign.h"
#include "ui_osdesign.h"

OSDesign::OSDesign(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSDesign)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
           QBrush(QPixmap(":/images/images/back1.jpg").scaled( // 缩放背景图.
           this->size(),
           Qt::IgnoreAspectRatio,
           Qt::SmoothTransformation))); // 使用平滑的缩放方式
        this->setPalette(palette); // 至此, 已给widget加上了背景图.
}

OSDesign::~OSDesign()
{
    delete ui;
}

void OSDesign::on_ProcessScheduleBtn_clicked()
{
    //进入进程调度模拟页面
    this->page_process.setWindowTitle("进程调度可视化模拟");
    page_process.show();
    //this->hide();
}

void OSDesign::on_JobScheduleBtn_clicked()
{
    //进入作业调度模拟页面
    this->page_job.setWindowTitle("作业调度算法衡量计算");
    page_job.show();
    //this->hide();
}

void OSDesign::on_PageReplacementBtn_clicked()
{
    this->pageReplace.setWindowTitle("页面调度算法模拟");
    pageReplace.show();
    //this->hide();
}

void OSDesign::on_DiskScheduleBtn_clicked()
{
    this->pageDisk.setWindowTitle("磁道调度算法模拟");
    pageDisk.show();
    //this->hide();
}

void OSDesign::on_ProcessManagerBtn_clicked()
{
    this->processmana.setWindowTitle("进程管理器（Windows)");
    processmana.show();
}
