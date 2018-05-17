/********************************************************************
    created:      2018/01/13
    created:      13:1:2018    17:56
    filename:     c:\Users\maoxd\documents\visual studio 2017\Projects\ThreadPool2\ThreadPool2\TaskObserver.h
    file path:    c:\Users\maoxd\documents\visual studio 2017\Projects\ThreadPool2\ThreadPool2
    file base:    TaskObserver
    file ext:     h
    author:       maoxd

    purpose:      Abstract base observer for all observer class, delay the observer of the task to a derived class
    usage:        Derived observer class from this and Implement the interfece of Response to get the task processing results
*********************************************************************/
#pragma once

#include <memory> // for std::shared_ptr

// predeclaration
class Task;


class TaskObserver
{
public:
    TaskObserver();
    ~TaskObserver();

    // implement this method to get the task processing results
    virtual void Response(const Task* context) = 0;
};

