#include "opt.h"
#include<iostream>
using namespace std;

OPT::OPT()
{

}

int OPT::exist(int a, int *page, int startid, int endid)
{
    for(int i=startid;i<endid;i++)
    {
        if(a==page[i])
        {
            return i;   //返回其在访问串中的索引
        }
    }
    return -1;
}

int OPT::choose(int taskid, int *page, int *task, int tasksize, int pagesize)
{
    //选取最优页
    int *time = new int[pagesize];
    int max =999;
    int tid;
    int t=0,position=0;

    for(int i=0,j=0;i<pagesize;i++,j++)
    {
        tid = exist(page[i],task,taskid,tasksize);
        //找出page数组中的值在访问串中出现的位置
        if(tid==-1)
        {
            time[j]=max;
            //如果当前值在后续串中不再出现，则把时间值记为最大
            //即不再访问的页
        }
        else
        {
            time[j]=tid;    //出现的话，记录下次出现时在访问串中的索引
        }
        //找出page数组的值在访问串下次出现的索引，并记录
    }

    for(int i=0;i<pagesize;i++)
    {
        if(time[i]>t)
        {
            t = time[i];
            position = i;
            // 找出page数组中下次出现的索引最长的那一个，并记录其在page数组中的索引
        }
    }
    return position;
}

void OPT::work(int *task, int taskid, int *page, int tasksize, int pagesize, int &pageIndex, int &lackpage)
{
    if(exist(task[taskid],page,0,pageIndex)==-1)
    {
        //缺页情况
        lackpage++;
        if(pageIndex<pagesize)
        {
            page[pageIndex]=task[taskid];
            pageIndex++;
        }
        else
        {
            int position = choose(taskid,page,task,tasksize,pagesize);
            page[position] = task[taskid];  //替换页面
        }
    }
}
