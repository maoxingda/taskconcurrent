#include "stdafx.h"
#include "Log.h"
#include <windows.h>
#include <ctime>


std::recursive_mutex io;

const char* log_level[] =  \
{                          \
    "[ERROR  ]",           \
    "[WARNING]",           \
    "[INFO   ]",           \
    "[DEBUG  ]"            \
};

Log::Log(const char* lpszName)
    : m_lpszName(lpszName)
{
    std::lock_guard<decltype(io)> lock(io);

    printf("%s [%s] [%06x] [%s] in. \r\n", log_level[2], date().c_str(), ::GetCurrentThreadId(), m_lpszName);
}


Log::~Log()
{
    std::lock_guard<decltype(io)> lock(io);

    printf("%s [%s] [%06x] [%s] out. \r\n", log_level[2], date().c_str(), ::GetCurrentThreadId(), m_lpszName);
}

std::string date()
{
    char szTime[256];

    SYSTEMTIME time;
    GetLocalTime(&time);

    sprintf_s(szTime, "%04d-%02d-%02d %02d:%02d:%02d:%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

    return szTime;
}
