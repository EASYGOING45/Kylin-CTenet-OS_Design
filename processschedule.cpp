#include "processschedule.h"
#include "ui_processschedule.h"
#include"addprocess.h"
#include"processitem.h"
#include"ui_processitem.h"
#include"choosealgo.h"
#include "ui_choosealgo.h"

ProcessSchedule::ProcessSchedule(QWidget *parent) : QWidget(parent),
                                                    ui(new Ui::ProcessSchedule)
{
    ui->setupUi(this);
    this->setWindowTitle("CPU调度模拟系统");

    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(":/images/images/widget3.jpg").scaled( // 缩放背景图.
                         this->size(), Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation))); // 使用平滑的缩放方式
    this->setPalette(palette);                        // 至此, 已给widget加上了背景图.

    this->type = 0; //用于控制所使用的调度算法
    this->backupNum = -1;
    this->processNum = 0;
    this->sliceTime = 0;
    this->runningProcs = new PCB();

    // 初始化数组
    this->initReadyArray();
    this->initBackupArray();
    this->initSuspendArray();

    // 取运行进程的优先级、就绪队列第一个进程的优先级（初始化都为0）
    priority_run = runningProcs->getPriority();
    priority_ready1st = ready[0].getPriority();

    // 短作业优先算法
    myTimer_SF = new QTimer(this); // 创建定时器 短作业优先算法
    connect(myTimer_SF, SIGNAL(timeout()), this, SLOT(refreshProcs_SF()));

    // 时间片轮转算法
    myTimer_RR = new QTimer(this);
    connect(myTimer_RR, SIGNAL(timeout()), this, SLOT(refreshProcs_RR()));
}

ProcessSchedule::~ProcessSchedule()
{
    delete ui;
}

void ProcessSchedule::receiveSF()
{
    type = 1;
    ui->lab_type->setText("短作业优先算法");

    chooseAlgo->close();

    // 向就绪队列数组中传最多道数个数组
    for (; processNum < NUM_OF_PROCESS; processNum++)
    {
        if (backup[0].getPriority() == 0)
        {
            qDebug() << "后备队列第0个数据为空";
            break;
        }
        else
        {
            ready[processNum] = backup[0];
            // 删除后备队列数组中的第一条数据
            delFirstOfBackup();
        }
    }

    // 若选择短作业优先调度，则给就绪队列数组排序
    bubbleSort(ready);
    // 刷新就绪队列界面
    readyToUi();
    // 刷新后备队列ui界面
    backupToUi();
}

// 待完成
void ProcessSchedule::receiveRR()
{
}

void ProcessSchedule::initReadyArray()
{
    // 初始化就绪队列数组
    for (int i = 0; i < NUM_OF_PROCESS; i++)
    {
        ready[i].setDefaultPCB();
    }
}

void ProcessSchedule::initBackupArray()
{
    // 初始化后备队列数组
    for (int i = 0; i < 100; i++)
    {
        backup[i].setDefaultPCB();
    }
}

void ProcessSchedule::initSuspendArray()
{
    // 初始化阻塞队列数组
    for (int i = 0; i < NUM_OF_PROCESS; i++)
    {
        suspend[i].setDefaultPCB();
    }
}

// receivePCB(QString PID,QString status,int priority,int runtime) // 添加进程的槽函数
void ProcessSchedule::receivePCB(QString PID, QString status, int priority, int runtime)
{
    qDebug() << "ReceivePCB()";
    PCB *pcb = new PCB(PID, status, priority, runtime);
    pcb->setMaxRuntime(runtime); // 设置最大运行时间
    backupNum++;
    backup[backupNum] = *pcb; // 将后备队列的数据填入后备队列数组中去

    ProcessItem *processitem = new ProcessItem();
    QListWidgetItem *item = new QListWidgetItem;

    // 向processItem中的tableView中填入数据
    model = new QStandardItemModel();
    model->setItem(0, 0, new QStandardItem(PID));                           // 进程PID
    model->setItem(0, 1, new QStandardItem(status));                        // 进程状态
    model->setItem(0, 2, new QStandardItem(QString::number(priority, 10))); // 进程优先级
    model->setItem(0, 3, new QStandardItem(QString::number(runtime, 10)));  // 进程运行时间

    processitem->ui->PCBInfo->setModel(model);
    processitem->ui->btn_unsuspend->hide();
    processitem->ui->btn_suspend->setEnabled(false);
    processitem->ui->progressBar->setValue(0);
    processitem->ui->btn_suspend->setEnabled(false);

    // 将自定义的进程item与QListWidgetItem绑定
    ui->backupQue->addItem(item);
    item->setSizeHint(QSize(320, 50));
    ui->backupQue->setItemWidget(item, processitem);

    qDebug() << "进程PID：" << PID << "进程状态：" << status << "进程优先级：" << priority << "进程运行时间：" << runtime;
}

// 选择算法按钮槽函数
void ProcessSchedule::on_btn_choose_clicked()
{
    //type ==0 代表还未选择调度算法，尚且处于调度模拟系统的准备阶段
    if (type == 0)
    {
        chooseAlgo = new class chooseAlgo();
        chooseAlgo->show();

        // 建立连接chooseAlgo中的短作业优先算法与计时器的信号与槽 槽函数机制非常的巧妙
        connect(chooseAlgo->ui->btn_SF, SIGNAL(clicked()), this, SLOT(receiveSF()));

        // 建立连接chooseAlgo中的时间片轮转算法与计时器的信号与槽
        connect(chooseAlgo->ui->btn_RR,SIGNAL(cliecked()),this,SLOT(receiveRR()));
    }

    // 向就绪队列数组中传最多六个进程
    for (; processNum < NUM_OF_PROCESS; processNum++)
    {
        // 按顺序永远传入第一个数据
        if (backup[0].getPriority() == 0)
        {
            qDebug() << "后备队列第0个数据为空";
            break;
        }
        else
        {
            ready[processNum] = backup[0];
            // 删除后备队列数组中的第一条数据
            delFirstOfBackup();
        }
    }

    // 若选择短作业优先调度，则给就绪队列数组排序
    if (type == 1)
    {
        bubbleSort(ready);
        readyToUi();
    }

    // 刷新就绪队列界面
    readyToUi();
    // 刷新后备队列ui界面
    backupToUi();
}

// 开始调度按钮槽函数
void ProcessSchedule::on_btn_start_clicked()
{
    ui->lab_type->setText("调度中......");
    ui->btn_start->setEnabled(false);

    // 若选择短作业优先算法
    if (type == 1)
    {
        // 计时器开始计时，频率为1000ms=1s
        myTimer_SF->start(1000);

        // 取就绪队列中的第一条数据，放入CPU调度中
        firstOfReadyToRunningUi();
        // 删除就绪队列中的第一条数据
        delFirstOfReady();
        // 刷新就绪队列的ui界面
        readyToUi();
    }

    // 未完成
}

void ProcessSchedule::on_btn_pause_clicked()
{
    if (type == 1)
        myTimer_SF->stop();
    if (type == 2)
        myTimer_RR->stop();
    ui->lab_CPUScheInfo->setText("暂停调度");
    ui->btn_pause->setEnabled(false);
}

void ProcessSchedule::on_btn_continue_clicked()
{
    if (type == 1)
        myTimer_SF->start(1000);
    if (type == 2)
        myTimer_RR->start(1000);
    ui->lab_CPUScheInfo->setText("调度中...");
    ui->btn_pause->setEnabled(true);
}

// 添加进程按钮槽函数
void ProcessSchedule::on_btn_addProcess_clicked()
{
    addProcess = new AddProcess();
    // 发送添加进程的信号
    connect(addProcess, SIGNAL(sendPCB(QString, QString, int, int)), this, SLOT(receivePCB(QString, QString, int, int)));
    addProcess->show(); // 显示添加进程的窗口
}

void ProcessSchedule::on_btn_reset_clicked()
{
    ui->lab_CPUScheInfo->setText("CPU调度");
    ui->lab_type->setText("调度方式");
    if (type == 1)
        myTimer_SF->stop();
    if (type == 2)
        myTimer_RR->stop();
    // 初始化所有变量
    initReadyArray();
    initBackupArray();
    initSuspendArray();
    backupNum = -1;
    processNum = 0;
    type = 0;
    sliceTime = 0;
    runningProcs = new PCB();
    // 设置开始调度按钮为可用
    ui->btn_start->setEnabled(true);
    ui->btn_pause->setEnabled(true);
    // 清空所有ui控件的item
    ui->backupQue->clear();
    ui->readyQue->clear();
    ui->runningProcs->clear();
    ui->scheInfo->clear();
    ui->suspendQue->clear();
}

// SF调度算法槽函数刷新就绪队列中数据的优先级、运行时间
void ProcessSchedule::refreshProcs_SF()
{
    ui->lab_CPUScheInfo->setText("调度中......");

    // 取运行进程的优先级、就绪队列第一个进程的优先级
    priority_run = runningProcs->getPriority();
    priority_ready1st = ready[0].getPriority();

    // 如果内存中进程数未达到道数上限且后备队列第一条数据不为空，则自动从后备队列中添加进程
    if (backup[0].getPriority() != 0)
    {
        for (; processNum < NUM_OF_PROCESS;)
        {
            if (backup[0].getPriority() == 0)
            {
                break; // 后备队列第一条数据为空，跳出循环
            }

            firstOfBackToReady(); // 将后备队列的第一条数据加入到就绪队列
            delFirstOfBackup();   // 删除后备队列的第一条数据
            backupToUi();         // 刷新后备队列的ui界面
        }
    }

    // 进程抢占：当就绪队列的第一条数据的优先级大于运行进程时发生抢占现象
    if (priority_ready1st > priority_run)
    {
        ui->lab_CPUScheInfo->setText("进程抢占中......");

        // 被抢占的进程重新加入就绪队列
        runningToReady();
        // 就绪队列的第一个进程加入运行队列
        firstOfReadyToRunningUi();
        runningToUi(); // 刷新运行进程的ui界面

        // 在就绪队列中删除第一个进程
        delFirstOfReady();
        readyToUi();
        // 对就绪队列进行排序，更新界面
        bubbleSort(ready);
        readyToUi();
    }

    // 运行进程的运行时间减1，优先级-1，运行时间为0时修改状态，输出在进程信息TableWidget中
    if (runningProcs->getPriority() != 0 && runningProcs->getRuntime() - 1 != 0)
    {
        runningProcs->delPriority(1);
        runningProcs->delRuntime(1);

        // 刷新UI界面上的运行调度界面
        runningToUi();
    }
    else
    {
        runningProcs->setStatus("终止");
        // 在进程调度信息处输出终止进程的信息
        finishToInfo();
        // 就绪队列第一个进程加入RunningProcs中
        firstOfReadyToRunningUi();
        // 在就绪队列中删除该条信息
        delFirstOfReady();

        // 给就绪进程数组重新排序
        bubbleSort(ready);
        // 刷新就绪列表ui界面
        readyToUi();
    }

    // 就绪队列中等待的进程的优先级+1
    for (int i = 0; i < NUM_OF_PROCESS && ready[i].getPriority() != 0; i++)
    {
        ready[i].addPriority(1);
    }
    // 刷新就绪列表ui界面
    readyToUi();
    // 刷新挂起列表ui界面
    suspendToUi();
}

// 待完成
void ProcessSchedule::refreshProcs_RR()
{
}

// 将就绪队列中的进程按照优先级进行降序排序
void ProcessSchedule::bubbleSort(PCB *array)
{
    for (int i = 0; i < NUM_OF_PROCESS - 1; i++)
    {
        for (int j = 0; j < NUM_OF_PROCESS - i - 1; j++)
        {
            if (array[j].getPriority() < array[j + 1].getPriority())
            {
                PCB temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

// 删除后备队列数组中的第一条数据
void ProcessSchedule::delFirstOfBackup()
{
    qDebug() << "删除后备队列第一条数据";
    int i;
    for (i = 0; backup[i + 1].getPriority() != 0; i++)
    {
        backup[i] = backup[i + 1];
    }
    for (; i < 100; i++)
    {
        backup[i].setDefaultPCB();
    }
    backupNum--;
}

// 删除就绪队列数组中的第一条数据
void ProcessSchedule::delFirstOfReady()
{
    qDebug() << "就绪队列第一条数据删除成功";
    for (int i = 0; i < NUM_OF_PROCESS; i++)
    {
        if (i == NUM_OF_PROCESS - 1 || ready[i + 1].getPriority() == 0)
        {
            ready[i].setDefaultPCB();
        }
        else
        {
            ready[i] = ready[i + 1];
        }
    }
}

// 删除PID对应的就绪进程
void ProcessSchedule::delOneOfReady(QString PID)
{
    for (int i = 0; i < NUM_OF_PROCESS; i++)
    {
        if (ready[i].getPID() == PID)
        {
            ready[i].setDefaultPCB();
            break;
        }
    }
    readyToUi();
}

// 删除PID的挂起进程
void ProcessSchedule::delOneOfSuspend(QString PID)
{
    for (int i = 0; i < NUM_OF_PROCESS; i++)
    {
        if (suspend[i].getPID() == PID)
        {
            qDebug() << "删除一条挂起进程";
            suspend[i].setDefaultPCB();
            break;
        }
    }
    suspendToUi();
}

// 将后备队列的第一条数据加入到就绪队列
void ProcessSchedule::firstOfBackToReady()
{
    for (int i = 0; i < NUM_OF_PROCESS; i++)
    {
        if (ready[i].getPriority() == 0)
        {
            ready[i] = backup[0];
            if (ready[i].getPriority() != 0)
            {
                processNum++; // 内存中进程个数加一
                qDebug() << "内存中进程个数加一";
            }
            break;
        }
    }
}

// 将被阻塞的进程加入到阻塞队列
void ProcessSchedule::workToSuspend(PCB pcb)
{
    QString PID = pcb.getPID();
    bool isInSuspendArray = false;
    qDebug() << "该进程被阻塞，进程名为：" + PID;
    for (int i = 0; i < NUM_OF_PROCESS; i++)
    {
        if (suspend[i].getPID() == PID)
        {
            isInSuspendArray = true;
            break;
        }
    }

    if (!isInSuspendArray)
    {
        for (int i = 0; i < NUM_OF_PROCESS; i++)
        {
            if (suspend[i].getPriority() == 0)
            {
                suspend[i] = pcb;
                break;
            }
        }
    }
}

// 将被解除阻塞的进程加入到就绪队列中
void ProcessSchedule::suspendToReady(PCB pcb)
{
    QString PID = pcb.getPID();
    bool isInReadyArray = false;
    qDebug() << "该进程被解除阻塞，进程名为：" + PID;
    for (int i = 0; i < NUM_OF_PROCESS; i++)
    {
        if (ready[i].getPID() == PID) // 判断就绪队列中是否已存在该进程，避免重复加入
        {
            isInReadyArray = true;
            break;
        }
    }

    if (!isInReadyArray) // 就绪队列中不存在该进程
    {
        for (int i = 0; i < NUM_OF_PROCESS; i++)
        {
            if (ready[i].getPriority() == 0)
            {
                ready[i] = pcb;
                break;
            }
        }
    }
}

// 将运行中的进程重新加入到就绪队列中（被抢占的情况）
void ProcessSchedule::runningToReady()
{
    for (int i = 0; i < NUM_OF_PROCESS; i++)
    {
        if (ready[i].getPriority() == 0)
        {
            ready[i] = *runningProcs;
            qDebug() << "成功将被抢占的进程加入就绪队列，且该进程PID=" + ready[i].getPID();
            break;
        }
    }
}

// 刷新就绪队列的UI界面
void ProcessSchedule::readyToUi()
{
    ui->readyQue->clear();
    for (int i = 0; i < NUM_OF_PROCESS; i++)
    {
        if (ready[i].getPriority() != 0)
        {
            QString PID = ready[i].getPID();
            QString status = "就绪";
            int priority = ready[i].getPriority();
            int max_runtime = ready[i].getMaxRuntime();
            int runtime = ready[i].getRuntime();
            ProcessItem *processitem = new ProcessItem();
            QListWidgetItem *item = new QListWidgetItem;

            // 往processItem中的tableView中填入数据
            model = new QStandardItemModel();
            model->setItem(0, 0, new QStandardItem(PID));
            model->setItem(0, 1, new QStandardItem(status));
            model->setItem(0, 2, new QStandardItem(QString::number(priority, 10)));
            model->setItem(0, 3, new QStandardItem(QString::number(runtime, 10)));
            // processitem->ui->PCBInfo->setModel(model);
            processitem->setModel(model);
            processitem->setSuspendPID(PID);
            processitem->ui->btn_unsuspend->setEnabled(false);
            processitem->ui->btn_unsuspend->hide();
            processitem->ui->progressBar->setRange(0, max_runtime);
            processitem->ui->progressBar->setValue(max_runtime - runtime);

            // 将自定义的进程item与QListWidgetItem绑定
            ui->readyQue->addItem(item);
            item->setSizeHint(QSize(320, 50));
            ui->readyQue->setItemWidget(item, processitem);

            // 给每个就绪进程增加一个挂起监听器
            connect(processitem, SIGNAL(sendWorkToSuspend(QString)), this, SLOT(receiveReadyToSuspend(QString)));
        }
    }
}

// 阻塞队列的槽函数
void ProcessSchedule::receiveReadyToSuspend(QString PID)
{
    qDebug() << "receiveReadyToSuspend......";
    for (int i = 0; i < NUM_OF_PROCESS; i++)
    {
        if (ready[i].getPID() == PID)
        {
            // 将被阻塞的进程加入阻塞队列
            workToSuspend(ready[i]);
            // 更新阻塞队列的UI界面
            suspendToUi();
            // 删除就绪队列中的该进程
            delOneOfReady(PID);
            // 更新就绪队列的UI界面
            readyToUi();
            break;
        }
    }
}

// 阻塞进程的槽函数（运行进程）
void ProcessSchedule::receiveRunningToSuspend(QString PID)
{
    qDebug() << "receiveRunningToSuspend...";

    // 将运行进程加入挂起队列
    workToSuspend(*runningProcs);
    // 更新挂起队列的ui界面
    suspendToUi();
    // 将就绪队列第一条数据加入到运行列表
    firstOfReadyToRunningUi();
    // 删除就绪队列第一条数据
    delFirstOfReady();
    // 刷新就绪队列界面
    readyToUi();
}

// 解除阻塞队列的槽函数
void ProcessSchedule::receiveSuspendToReady(QString PID)
{
    qDebug() << "receiveSuspendToReady...";
    qDebug() << "被解挂的进程PID：" + PID;
    for (int i = 0; i < NUM_OF_PROCESS; i++)
    {
        if (suspend[i].getPID() == PID)
        {
            qDebug() << "receiveSuspendToReady...";
            // 将被解挂的进程加入就绪队列
            suspendToReady(suspend[i]);
            // 给就绪数组排序
            bubbleSort(ready);
            // 更新就绪队列的ui界面
            readyToUi();
            // 删除挂起队列中的该进程
            delOneOfSuspend(PID);
            // 更新挂起队列的ui界面
            suspendToUi();
            break;
        }
    }
}

// 将backup中的数据传入BackupQue中
void ProcessSchedule::backupToUi()
{
    ui->backupQue->clear();
    for (int i = 0; i < 100 && backup[i].getPriority() != 0; i++)
    {
        QString PID = backup[i].getPID();
        QString status = "后备";
        int priority = backup[i].getPriority();
        int runtime = backup[i].getRuntime();
        ProcessItem *processitem = new ProcessItem();
        QListWidgetItem *item = new QListWidgetItem;

        // 往processItem中的tableView中填入数据
        model = new QStandardItemModel();
        model->setItem(0, 0, new QStandardItem(PID));
        model->setItem(0, 1, new QStandardItem(status));
        model->setItem(0, 2, new QStandardItem(QString::number(priority, 10)));
        model->setItem(0, 3, new QStandardItem(QString::number(runtime, 10)));
        processitem->ui->PCBInfo->setModel(model);
        processitem->ui->progressBar->setValue(0);
        processitem->ui->btn_suspend->setEnabled(false);
        processitem->ui->btn_unsuspend->hide();

        // 将自定义的进程item与QListWidgetItem绑定
        ui->backupQue->addItem(item);
        item->setSizeHint(QSize(320, 50));
        ui->backupQue->setItemWidget(item, processitem);
    }
}

// 刷新runningProcs的数据显示
void ProcessSchedule::runningToUi()
{
    ui->runningProcs->clear();
    QString PID = runningProcs->getPID();
    QString status = "运行";
    int priority = runningProcs->getPriority();
    int max_runtime = runningProcs->getMaxRuntime();
    int runtime = runningProcs->getRuntime();
    ProcessItem *processitem = new ProcessItem();
    QListWidgetItem *item = new QListWidgetItem;

    model = new QStandardItemModel();
    model->setItem(0, 0, new QStandardItem(PID));
    model->setItem(0, 1, new QStandardItem(status));
    model->setItem(0, 2, new QStandardItem(QString::number(priority, 10)));
    model->setItem(0, 3, new QStandardItem(QString::number(runtime, 10)));
    processitem->ui->PCBInfo->setModel(model);
    processitem->ui->btn_unsuspend->show();
    processitem->ui->btn_unsuspend->hide();
    processitem->ui->btn_suspend->setEnabled(true);
    processitem->ui->progressBar->setRange(0, max_runtime);
    processitem->ui->progressBar->setValue(max_runtime - runtime);

    ui->runningProcs->addItem(item);
    item->setSizeHint(QSize(320, 50));
    ui->runningProcs->setItemWidget(item, processitem);

    // 给每个运行中的进程加一个挂起监听器
    connect(processitem, SIGNAL(sendWorkToSuspend(QString)), this, SLOT(receiveRunningToSuspend(QString)));
}

// 刷新阻塞队列的UI界面
void ProcessSchedule::suspendToUi()
{
    ui->suspendQue->clear();
    for (int i = 0; i < NUM_OF_PROCESS; i++)
    {
        if (suspend[i].getPriority() != 0)
        {
            QString PID = suspend[i].getPID();
            QString status = "挂起";
            int priority = suspend[i].getPriority();
            int runtime = suspend[i].getRuntime();
            int max_runtime = suspend[i].getMaxRuntime();
            ProcessItem *processitem = new ProcessItem();
            QListWidgetItem *item = new QListWidgetItem;

            // 往processItem中的tableView中填入数据
            model = new QStandardItemModel();
            model->setItem(0, 0, new QStandardItem(PID));
            model->setItem(0, 1, new QStandardItem(status));
            model->setItem(0, 2, new QStandardItem(QString::number(priority, 10)));
            model->setItem(0, 3, new QStandardItem(QString::number(runtime, 10)));
            processitem->setModel(model);
            processitem->setSuspendPID(PID);
            processitem->ui->progressBar->setRange(0, max_runtime);
            processitem->ui->progressBar->setValue(max_runtime - runtime);
            // 隐藏挂起的按钮，显示解挂按钮
            processitem->ui->btn_suspend->hide();

            // 将自定义的进程item与QListWidgetItem绑定
            ui->suspendQue->addItem(item);
            item->setSizeHint(QSize(320, 50));
            ui->suspendQue->setItemWidget(item, processitem);

            // 给每个挂起进程增加一个解挂监听器
            connect(processitem, SIGNAL(sendSuspendToReady(QString)), this, SLOT(receiveSuspendToReady(QString)));
        }
    }
}

// 取就绪队列中的第一条数据，放入CPU中模拟调度
void ProcessSchedule::firstOfReadyToRunningUi()
{
    // 此时内存中进程个数不变
    *runningProcs = ready[0];
    if (runningProcs->getPriority() != 0)
    {
        ui->runningProcs->clear();
        QString PID = runningProcs->getPID();
        QString status = "运行";
        int priority = runningProcs->getPriority();
        int runtime = runningProcs->getRuntime();
        int max_runtime = runningProcs->getMaxRuntime();
        ProcessItem *processitem = new ProcessItem();
        QListWidgetItem *item = new QListWidgetItem;

        model = new QStandardItemModel();
        model->setItem(0, 0, new QStandardItem(PID));
        model->setItem(0, 1, new QStandardItem(status));
        model->setItem(0, 2, new QStandardItem(QString::number(priority, 10)));
        model->setItem(0, 3, new QStandardItem(QString::number(runtime, 10)));
        processitem->ui->PCBInfo->setModel(model);
        processitem->ui->btn_unsuspend->hide();
        processitem->ui->btn_suspend->setEnabled(true);
        processitem->ui->progressBar->setRange(0, max_runtime);
        processitem->ui->progressBar->setValue(max_runtime - runtime);

        ui->runningProcs->addItem(item);
        item->setSizeHint(QSize(320, 50));
        ui->runningProcs->setItemWidget(item, processitem);
    }
    else
    {
        qDebug() << "进程已全部完成！";
        // myTimer->stop();
        ui->runningProcs->clear();
        ui->lab_CPUScheInfo->setText("调度结束");
    }
}

// 将运行完成的进程加入到进程调度的TableWidget中进行显示
void ProcessSchedule::finishToInfo()
{
    if (runningProcs->getPriority() != 0)
    {
        qDebug() << "完成一个进程，内存中进程数减一";
        processNum--; // 内存中进程个数减一
        QString PID = runningProcs->getPID();
        QString status = "完成";
        int priority = runningProcs->getPriority();
        int runtime = runningProcs->getRuntime();
        ProcessItem *processitem = new ProcessItem();
        QListWidgetItem *item = new QListWidgetItem;

        model = new QStandardItemModel();
        model->setItem(0, 0, new QStandardItem(PID));
        model->setItem(0, 1, new QStandardItem(status));
        model->setItem(0, 2, new QStandardItem(QString::number(priority, 10)));
        model->setItem(0, 3, new QStandardItem(QString::number(runtime, 10)));
        processitem->ui->PCBInfo->setModel(model);
        processitem->ui->progressBar->setValue(100);
        processitem->ui->btn_suspend->setEnabled(false);
        processitem->ui->btn_unsuspend->hide();

        ui->scheInfo->addItem(item);
        item->setSizeHint(QSize(320, 50));
        ui->scheInfo->setItemWidget(item, processitem);
    }
}
