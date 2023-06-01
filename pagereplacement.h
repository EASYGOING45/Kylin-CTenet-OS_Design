#ifndef PAGEREPLACEMENT_H
#define PAGEREPLACEMENT_H

#include <QMainWindow>
#include<QFileDialog>
#include<QFileInfo>
#include<QMessageBox>
#include<QTime>

#include"fifo.h"
#include"lru.h"
#include"opt.h"

namespace Ui {
class PageReplacement;
}

class PageReplacement : public QMainWindow
{
    Q_OBJECT

public:
    explicit PageReplacement(QWidget *parent = nullptr);
    ~PageReplacement();
    QString pageAl;                 // 选择的算法
    int *task;                      // 访问串数组
    int *page;                      // 页面数组
    char *pgLack;                   // 缺页标记数组
    int pageSize  =0;               // 内存块数量
    int taskSize = 0;               // 访问串长度
    int pageIndx = 0;               // 页面数组索引
    int lackpage = 0;               // 缺页数
    void mwsleep(int m);            // 延迟函数
    void vilack();                  // 缺页率计算函数
    FIFO *al_fifo  = new FIFO();    // fifo算法对象声明
    LRU *al_lru = new LRU();        // lru算法对象声明
    OPT *al_opt = new OPT();        // opt算法对象声明
private slots:
    void openfile();                // 打开访问串文件
    void filecreat();               // 创建访问串文件
    void getslider();               // 内存块滑块改变响应
    void switchPage();              // 算法页面切换函数
    void onerun();                  // 单步模拟
    void allclear();                // 重置
    void run();                     // 模拟

private:
    Ui::PageReplacement *ui;
};

#endif // PAGEREPLACEMENT_H
