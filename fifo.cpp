#include "fifo.h"

FIFO::FIFO()
{

}

bool FIFO::exist(int a, int *page, int pageIndex)
{
    //判断page数组中是否有a，pageIndex<=pageSize
    for(int i=0;i<pageIndex;i++)
    {
        if(a==page[i])
        {
            return true;
        }
    }
    return false;
}

void FIFO::work(int a, int *page, int pagesize, int &pageIndex, int &lackpage)
{
    //参数分别为 当前页 页面数组 页框数 页号 缺页数
    //   算法设计 把不符合该算法的值(也就是page数组的第一个移除),把当前值加入数组。
    if(!exist(a,page,pageIndex))
    {
        //如果缺少当前所需页号
        lackpage++;
        if(pageIndex<pagesize)
        {
            //如果索引<pagesize,则说明page中存在-1.即为空页
            page[pageIndex] = a;
            pageIndex++;
        }
        else
        {
            for(int j=0;j<pagesize-1;j++)
            {
                page[j] = page[j+1];
            }
            page[pagesize-1]=a;
        }
    }
}
