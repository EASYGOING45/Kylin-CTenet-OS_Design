#include "choosealgo.h"
#include "ui_choosealgo.h"

chooseAlgo::chooseAlgo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chooseAlgo)
{
    this->setWindowTitle("选择调度算法");
    ui->setupUi(this);

    this->setAutoFillBackground(true);  //确保背景图正确显示
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
           QBrush(QPixmap(":/images/images/choose1.jpg").scaled( // 缩放背景图.
           this->size(),
           Qt::IgnoreAspectRatio,
           Qt::SmoothTransformation))); // 使用平滑的缩放方式
    this->setPalette(palette);  //成功添加背景图
}

chooseAlgo::~chooseAlgo()
{
    delete ui;
}
