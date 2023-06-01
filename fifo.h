#ifndef FIFO_H
#define FIFO_H

//实现页式存储管理中的FIFO算法
class FIFO
{
public:
    FIFO();
    bool exist(int a,int page[],int pageIndex); //用于判断是否存在页
    void work(int a,int page[],int pagesize,int &pageIndex,int &lackpage);
};

#endif // FIFO_H
