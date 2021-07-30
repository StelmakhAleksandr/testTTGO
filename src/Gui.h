#pragma once

#include <TFT_eSPI.h>
#include <lvgl.h>
#include <lv_png.h>
#include <functional>
#include "ITask.h"

class GUI : public ITask {
public:
    void init();
    void task() override;
private:
    lv_disp_draw_buf_t draw_buf;
    lv_color_t buf[TFT_WIDTH * 10];
    static TFT_eSPI tft_;
    static void flush(_lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
};
