#pragma once

#include <Arduino.h>
#include <functional>
#include <string>

class ITask {
public:
    static void createTask(std::string name, ITask *task);
    static void createTaskInner(void *instance);
    virtual void task() = 0;
};
