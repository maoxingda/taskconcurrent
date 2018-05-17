#include "stdafx.h"
#include "../Inc/TaskManager.h"
#include "../../Demo/Log.h"


TaskManager::TaskManager( unsigned threadNumbers /*= 10u*/ )
    : m_pThreadPool(NULL)
    , m_uThreadNumbers(threadNumbers)
{
}

TaskManager::~TaskManager()
{
}

void TaskManager::Create()
{
    m_pThreadPool = CreateThreadpool(NULL);

    SetThreadpoolThreadMinimum(m_pThreadPool, m_uThreadNumbers);
    SetThreadpoolThreadMaximum(m_pThreadPool, 100);

    SubmitThreadpoolWork(CreateThreadpoolWork(&TaskManager::WaitTask, this, NULL));
}

void TaskManager::Destroy( bool bWait /*= true*/ )
{
    if (bWait)
    {
        while (!m_listTask.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
    else
    {
        CloseThreadpool(m_pThreadPool);
    }

    m_pThreadPool = NULL;
}

void TaskManager::AddTask(const std::shared_ptr<Task>& task)
{
    std::lock_guard<std::mutex> lock(m_mutexTaskList);

    m_listTask.push_back(task);
}

VOID NTAPI TaskManager::WaitTask(_Inout_ PTP_CALLBACK_INSTANCE instance, _Inout_opt_ PVOID context, _Inout_ PTP_WORK work)
{
    TaskManager* ptp = static_cast<TaskManager*>(context);

    if (ptp && ptp->m_pThreadPool)
    {
        while (ptp->m_pThreadPool)
        {
            ptp->WaitTask();

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
    else
    {
        LOGERROR("no thread pool has been created yet. \r\n");
    }
}

void TaskManager::WaitTask()
{
    std::lock_guard<std::mutex> lock(m_mutexTaskList);

    auto citer = std::begin(m_listTask);
    auto end   = std::end(m_listTask);

    while (end != citer)
    {
        std::shared_ptr<Task> spTask = *citer;

        switch (spTask->GetTaskStatus())
        {
        case Task::ready:
            SubmitThreadpoolWork(CreateThreadpoolWork(&Task::TaskHandler, spTask.get(), NULL));
            ++citer;
            break;
        case Task::done:
            m_listTask.erase(citer++);
            break;
        default:
            break;
        }
    }
}
