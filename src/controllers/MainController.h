#pragma once

#include "MainWindow.h"
#include "MainModel.h"

class MainController {
public:
    void init();
    void run();
    void setText(std::string text);
private:
    MainWindow window_;
    MainModel model_;
};