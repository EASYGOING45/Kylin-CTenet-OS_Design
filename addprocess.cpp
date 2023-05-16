#include "addprocess.h"
#include "ui_addprocess.h"

AddProcess::AddProcess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddProcess)
{
    ui->setupUi(this);
    this->setWindowTitle("添加新进程");

    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window,
           QBrush(QPixmap(":/images/images/bgi7.jpg").scaled( // 缩放背景图.
           this->size(),
           Qt::IgnoreAspectRatio,
           Qt::SmoothTransformation))); // 使用平滑的缩放方式
        this->setPalette(palette); // 至此, 已给widget加上了背景图.
}

AddProcess::~AddProcess()
{
    delete ui;
}

void AddProcess::on_btn_add_clicked()
{
    QString PID=ui->le_PID->text(); //获取控件的输入信息
    QString status="后备";
    int priority = ui->le_priority->text().toInt(); //将优先级化为整数
    int runtime = ui->le_runtime->text().toInt();

    //向Widget传参
    emit sendPCB(PID,status,priority,runtime);
}

void AddProcess::on_btn_random_clicked()
{
    QString status="后备";

    //随即生成PID
    int randPID=QRandomGenerator::global()->bounded(999,10000);
    QString PID="P"+QString::number(randPID,10);  //拼接生成PID
    ui->le_PID->setText(PID);

    //随机生成优先权
    int randPriority = QRandomGenerator::global()->bounded(50,200);
    QString priority = QString::number(randPriority,10);
    ui->le_priority->setText(priority);

    //随机生成runtime
    int randRuntime = QRandomGenerator::global()->bounded(5,30);
    QString runtime = QString::number(randRuntime,10);
    ui->le_runtime->setText(runtime);

    //向widget传参
    emit sendPCB(PID,status,priority.toInt(),runtime.toInt());
}

void AddProcess::on_btn_clear_clicked()
{
    ui->le_PID->clear();
    ui->le_runtime->clear();
    ui->le_priority->clear();
}
