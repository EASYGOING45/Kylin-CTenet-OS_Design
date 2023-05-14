#include "processitem.h"
#include "ui_processitem.h"

ProcessItem::ProcessItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessItem)
{
    ui->setupUi(this);
}

ProcessItem::~ProcessItem()
{
    delete ui;
}
