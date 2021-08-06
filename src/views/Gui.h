#pragma once

#include "GuiTask.h"
#include "WindowUpdateTask.h"
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <lv_png.h>
#include <functional>


class Gui {
public:
    void init();
    void runTask();
private:
    lv_disp_draw_buf_t drawBuf_;
    lv_color_t buf_[TFT_WIDTH * 10];
    TFT_eSPI tft_;
    lv_disp_drv_t dispDrv_;
    GuiTask guiTask_;
    WindowUpdateTask windowUpdateTask_;
    static std::function<void (lv_disp_drv_t *, const lv_area_t *, lv_color_t *)> onFlush;
    static void flush(lv_disp_drv_t *, const lv_area_t *, lv_color_t *);
    void flushInner(lv_disp_drv_t *, const lv_area_t *, lv_color_t *);
};
