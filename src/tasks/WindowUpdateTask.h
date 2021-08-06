#pragma once

#include "ITask.h"
#include "IWindow.h"
#include <functional>

class WindowUpdateTask : public ITask {
public:
    static void setCurrentWindow(IWindow *);
private:
    static IWindow *currentWindow_;
    void task() override;
};