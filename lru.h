#ifndef LRU_H
#define LRU_H


class LRU
{
public:
    LRU();
    bool exist(int a,int page[],int pageIndex);
    void work(int a,int page [],int pagesize,int & pageIndex,int & lackpage);
};

#endif // LRU_H
