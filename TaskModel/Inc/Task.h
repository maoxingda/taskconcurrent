/********************************************************************
    created:      2018/01/13
    created:      13:1:2018    17:28
    filename:     c:\Users\maoxd\documents\visual studio 2017\Projects\ThreadPool2\ThreadPool2\Task.h
    file path:    c:\Users\maoxd\documents\visual studio 2017\Projects\ThreadPool2\ThreadPool2
    file base:    Task
    file ext:     h
    author:       maoxd

    purpose:      Abstract base task for all concrete task class, delay the processing of the task to a derived class
    usage:        Derived task class from this and Implement the interfece of DoTask to process concrete task
*********************************************************************/
#pragma once

#include <memory>           // for std::enable_shared_from_this
#include <windows.h>        // for PTP_CALLBACK_INSTANCE PVOID PTP_WORK
#include "TaskObserver.h"


class Task : public std::enable_shared_from_this<Task>
{
public:
    Task(const unsigned taskID);
    ~Task();

    // status
    enum {ready = 1, done};

    // process
    static VOID NTAPI                   TaskHandler             (_Inout_ PTP_CALLBACK_INSTANCE instance, _Inout_opt_ PVOID context, _Inout_ PTP_WORK work);
    void                                TaskHandler             ();

    // identifier information
    unsigned                            GetTaskID               () const;

    // status
    unsigned                            GetTaskStatus           () const;

    // observer
    void                                SetTaskObserver         (TaskObserver* val);

private:
    // implement this method to process concrete task
    virtual void                        DoTask                  () = 0;

private:
    unsigned                            m_uTaskID;              // identifier
    unsigned                            m_uTaskStatus;          // status
    TaskObserver*                       m_pTaskObserver;        // observer
};

