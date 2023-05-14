#include "pcb.h"

PCB::PCB()
{
    this->PID="P0000";
    this->status="后备";
    this->priority=0;
    this->max_runtime=0;
    this->runtime=0;
}

//含参构造函数
PCB::PCB(QString PID,QString status,int priority,int runtime)
{
    this->PID=PID;
    this->status=status;
    this->priority=priority;
    this->runtime=runtime;
}

int PCB::getRuntime() const
{
    return runtime;
}

void PCB::setRuntime(int value)
{
    this->runtime=value;
}


void PCB::delRuntime(int value)
{
    if(runtime > 0)
    {
        runtime -= value;
    }
    else
    {
        return;
    }
}

QString PCB::getPID() const
{
    return PID;
}

void PCB::setPID(QString value)
{
    this->PID=value;
}

void PCB::setMaxRuntime(int value)
{
    this->max_runtime=value;
}

QString PCB::getStatus() const
{
    return status;
}

void PCB::setStatus(QString value)
{
    status = value;
}

int PCB::getPriority() const
{
    return priority;
}

int PCB::getMaxRuntime() const
{
    return max_runtime;
}

void PCB::setPriority(int value)
{
    priority = value;
}

void PCB::delPriority(int value)
{
    if(priority>0){
        priority -= value;
    }
    else
        return;
}

void PCB::addPriority(int value)
{
    priority += value;
}

void PCB::setDefaultPCB()
{
    PID = "P0000";
    status = "后备";
    priority = 0;
    runtime = 0;
}











