#include "stdafx.h"
#include "TaskConcrete.h"
#include "../TaskModel/TaskID.h"


TaskLogin::TaskLogin()
    : Task(TaskID::login)
    , m_bAuthentication(false)
{
}


TaskLogin::~TaskLogin()
{
}

void TaskLogin::SetUserName(const std::string& val)
{
    m_strUserName = val;
}

void TaskLogin::SetPassword(const std::string& val)
{
    m_strPassword = val;
}

bool TaskLogin::GetAuthentication() const
{
    return m_bAuthentication;
}

void TaskLogin::DoTask()
{
    if ("maoxd" == m_strUserName && "123456" == m_strPassword)
    {
        m_bAuthentication = true;
    }
}
