#include "IWindow.h"
#include "WindowUpdateTask.h"

IWindow::IWindow() {
    using std::placeholders::_1;
    onLoaded = std::bind(&WindowUpdateTask::setCurrentWindow, _1);
}