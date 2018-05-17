#include "stdafx.h"
#include "Logic.h"
#include "../TaskModel/TaskID.h"
#include "TaskConcrete.h"
#include "Log.h"


Logic::Logic( TaskManager& tm )
    : m_taskManager(tm)
{
}


Logic::~Logic()
{
}

void Logic::Login( std::string strUserName, std::string strPassword )
{
    IOLOG;

    std::shared_ptr<TaskLogin> spTask(new TaskLogin);

    if (spTask)
    {
        spTask->SetUserName(strUserName);
        spTask->SetPassword(strPassword);

        spTask->SetTaskObserver(this);

        m_taskManager.AddTask(spTask);
    }
}

void Logic::LoginResponse(const Task* context)
{
    IOLOG;

    const TaskLogin* pTask = dynamic_cast<const TaskLogin*>(context);

    if (pTask)
    {
        if (pTask->GetAuthentication())
        {
            LOGINFO("login success. \r\n");
        }
    }
}

void Logic::Response(const Task* context)
{
    switch (context->GetTaskID())
    {
    case TaskID::login:
        LoginResponse(context);
        break;
    default:
        break;
    }
}
