#include "stdafx.h"
#include "../Inc/Task.h"


Task::Task(const unsigned taskID)
    : m_uTaskID(taskID)
    , m_uTaskStatus(ready)
    , m_pTaskObserver(NULL)
{
}

Task::~Task()
{
}

VOID NTAPI Task::TaskHandler(_Inout_ PTP_CALLBACK_INSTANCE instance, _Inout_opt_ PVOID context, _Inout_ PTP_WORK work)
{
    Task* pTask = static_cast<Task*>(context);

    if (pTask)
    {
        pTask->TaskHandler();
    }
}

void Task::TaskHandler()
{
    DoTask();

    if (m_pTaskObserver)
    {
        m_pTaskObserver->Response(this);
    }

    m_uTaskStatus = done;
}

unsigned Task::GetTaskID() const
{
    return m_uTaskID;
}

unsigned Task::GetTaskStatus() const
{
    return m_uTaskStatus;
}

void Task::SetTaskObserver(TaskObserver* val)
{
    m_pTaskObserver = val;
}
