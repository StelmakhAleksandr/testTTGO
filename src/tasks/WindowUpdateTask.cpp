#include "WindowUpdateTask.h"

IWindow *WindowUpdateTask::currentWindow_ = nullptr; 

void WindowUpdateTask::setCurrentWindow(IWindow * window) {
    currentWindow_ = window;
}

void WindowUpdateTask::task() {
    while(true) {
        if(currentWindow_) {
            currentWindow_->update();
        }
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}