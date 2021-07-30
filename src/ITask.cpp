#include "ITask.h"

void ITask::createTask(std::string name, ITask *task) {
    xTaskCreatePinnedToCore(&ITask::createTaskInner, name.c_str(), 4096, task, 1, NULL, 1);
}

void ITask::createTaskInner(void *instance) {
    ITask *task = static_cast<ITask*>(instance);
    if(task) {
        task->task();
    }
}
