#pragma once

#include "IWindow.h"
#include <lvgl.h>

class BluetoothWindow : public IWindow {
public:
    void load() override;
    void update() override;
private:
};