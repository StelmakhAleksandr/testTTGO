#pragma once

#include "ITask.h"
#include <lvgl.h>

class GuiTask : public ITask {
private:
    void task() override;
};