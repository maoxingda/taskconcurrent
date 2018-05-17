// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../TaskModel/Inc/TaskManager.h"
#include "Logic.h"
#include <vld.h>


int main()
{
    TaskManager tm(2);
    tm.Create();

    Logic logic(tm);

    for (size_t i = 0; i < 3; i++)
    {
        logic.Login("maoxd", "123456");
    }

    getchar();

    tm.Destroy();

    return 0;
}

