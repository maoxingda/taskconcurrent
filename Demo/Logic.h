#pragma once
#include "../TaskModel/Inc/TaskObserver.h"
#include "../TaskModel/Inc/TaskManager.h"


class Logic : public TaskObserver
{
public:
    Logic(TaskManager& tm);
    ~Logic();

public:
    void Login(std::string strUserName, std::string strPassword);
    void LoginResponse(const Task* context);

private:
    virtual void Response(const Task* context) override;

private:
    TaskManager& m_taskManager;
};

