#pragma once

#include "MainModel.h"
#include "IWindow.h"
#include <lvgl.h>
#include <lv_gif.h>
#include <string>

class MainWindow : public IWindow {
public:
    void load() override;
    void update() override;
    void setModel(MainModel *model);
private:
    MainModel *model_;
    lv_obj_t *label_; 
};
