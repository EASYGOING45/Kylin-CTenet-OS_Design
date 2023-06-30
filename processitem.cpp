#include "processitem.h"
#include "ui_processitem.h"

ProcessItem::ProcessItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessItem)
{
    ui->setupUi(this);
    ui->progressBar->setStyleSheet("QProgressBar{border: 2px solid grey;border-radius: 5px;text-align: center;}"
                                       "QProgressBar::chunk{background-color: #CD96CD;width: 10px;margin: 0.5px;}");

    PID="";
    //设置表格列宽自适应TableView
    ui->PCBInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->PCBInfo->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //隐藏表头
    ui->PCBInfo->horizontalHeader()->hide();
    ui->PCBInfo->verticalHeader()->hide();
    //设置表格不可编辑
    ui->PCBInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

ProcessItem::~ProcessItem()
{
    delete ui;
}

void ProcessItem::setModel(QStandardItemModel *model)
{
    this->model = model;
    ui->PCBInfo->setModel(model);
}

void ProcessItem::setSuspendPID(QString PID)
{
    this->PID = PID;
}

QString ProcessItem::getSuspendPID()
{
    return PID;
}

//点击阻塞按钮
void ProcessItem::on_btn_suspend_clicked()
{
    emit sendWorkToSuspend(PID);        //这个是自定义信号
}

void ProcessItem::on_btn_unsuspend_clicked()
{
    emit sendSuspendToReady(PID);   //解除阻塞
}
