#include "lru.h"

LRU::LRU()
{

}

bool LRU::exist(int a, int *page, int pageIndex)
{
    for(int i=0;i<pageIndex;i++)
    {
        if(a==page[i])
        {
            int temp=page[i];
            for(int j=i;j<pageIndex-1;j++)
            {
                page[j]=page[j+1];
            }
            page[pageIndex-1]=temp;
            // 如果访问串当前值在page数组中纯在，则把当前值在的page数组的位置移至最后。也把最长时间未使用的值移到了最开始。
            return true;
        }
    }
    return false;
}


void LRU::work(int a, int *page, int pagesize, int &pageIndex, int &lackpage)
{
    if(!exist(a,page,pageIndex)) // 如果序列当前值不在page数组中
    {
        lackpage++;
        if(pageIndex<pagesize)   // 如果索引小于pagesize,则说明page中存在 -1 也就是空页！！
        {
            page[pageIndex]=a;
            pageIndex++;

        }
        else
        {
            for(int j=0;j<pagesize-1;j++)
            {
                page[j]=page[j+1];
            }
            page[pagesize-1]=a;
            //   算法设计 把不符合该算法的值(也就是page数组的第一个移除),把当前值加入数组。
        }

    }
}
