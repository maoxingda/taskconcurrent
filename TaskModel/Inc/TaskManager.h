/********************************************************************
    created:      2018/01/13
    created:      13:1:2018    18:15
    filename:     c:\Users\maoxd\documents\visual studio 2017\Projects\ThreadPool2\ThreadPool2\ThreadPool.h
    file path:    c:\Users\maoxd\documents\visual studio 2017\Projects\ThreadPool2\ThreadPool2
    file base:    ThreadPool
    file ext:     h
    author:       maoxd

    purpose:      task management
*********************************************************************/
#pragma once

#include "Task.h"
#include <mutex>        // for std::mutex
#include <list>         // for std::list


class TaskManager
{
public:
    TaskManager(unsigned threadNumbers = 10u);
    ~TaskManager();

public:
    void                                 Create                     ();
    void                                 Destroy                    (bool bWait = true);

    void                                 AddTask                    (const std::shared_ptr<Task>& task);

private:
    static VOID NTAPI                    WaitTask                   (_Inout_ PTP_CALLBACK_INSTANCE instance, _Inout_opt_ PVOID context, _Inout_ PTP_WORK work);
    void                                 WaitTask                   ();

private:
    PTP_POOL                             m_pThreadPool;
    unsigned                             m_uThreadNumbers;

    std::list< std::shared_ptr<Task> >   m_listTask;
    std::mutex                           m_mutexTaskList;
};

