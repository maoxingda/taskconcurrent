#pragma once
#include <mutex>
#include <string>


class Log
{
public:
    Log(const char* lpszName);
    ~Log();

private:
    const char* m_lpszName;
};

std::string date();

#define FUNCN __FUNCTION__
#define IOLOG Log log(FUNCN)

extern std::recursive_mutex io;
extern const char* log_level[];

#define LOGERROR(...)                                                                            \
{                                                                                                \
    std::lock_guard<decltype(io)> lock(io);                                                      \
    printf("%s [%s] [%06x] [%s] ", log_level[0], date().c_str(), ::GetCurrentThreadId(), FUNCN); \
    printf(__VA_ARGS__);                                                                         \
}

#define LOGWARNING(...)                                                                          \
{                                                                                                \
    std::lock_guard<decltype(io)> lock(io);                                                      \
    printf("%s [%s] [%06x] [%s] ", log_level[1], date().c_str(), ::GetCurrentThreadId(), FUNCN); \
    printf(__VA_ARGS__);                                                                         \
}

#define LOGINFO(...)                                                                             \
{                                                                                                \
    std::lock_guard<decltype(io)> lock(io);                                                      \
    printf("%s [%s] [%06x] [%s] ", log_level[2], date().c_str(), ::GetCurrentThreadId(), FUNCN); \
    printf(__VA_ARGS__);                                                                         \
}

#define LOGDEBUG(...)                                                                            \
{                                                                                                \
    std::lock_guard<decltype(io)> lock(io);                                                      \
    printf("%s [%s] [%06x] [%s] ", log_level[3], date().c_str(), ::GetCurrentThreadId(), FUNCN); \
    printf(__VA_ARGS__);                                                                         \
}
