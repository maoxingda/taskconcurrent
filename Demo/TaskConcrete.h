#pragma once
#include "../TaskModel/Inc/Task.h"
#include <string>


class TaskLogin : public Task
{
public:
    TaskLogin();
    ~TaskLogin();

    void SetUserName(const std::string& val);
    void SetPassword(const std::string& val);

    bool GetAuthentication() const;

private:
    virtual void DoTask() override;

private:
    std::string m_strUserName;
    std::string m_strPassword;

    bool        m_bAuthentication;
};

