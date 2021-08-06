#include "Gui.h"

std::function<void (lv_disp_drv_t *, const lv_area_t *, lv_color_t *)> Gui::onFlush;

void Gui::flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color) {
    onFlush(disp, area, color);
}

void Gui::flushInner(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    tft_.startWrite();
    tft_.setAddrWindow( area->x1, area->y1, w, h );
    tft_.pushColors((uint16_t*)&color->full, w * h, true);
    tft_.endWrite();
    lv_disp_flush_ready(disp);
}


void Gui::init() {
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;
    onFlush = std::bind(&Gui::flushInner, this, _1, _2, _3);

    tft_.begin();
    tft_.setRotation(1); 
    lv_disp_draw_buf_init(&drawBuf_, buf_, NULL, TFT_WIDTH * 10);

    lv_disp_drv_init(&dispDrv_);
    dispDrv_.hor_res = TFT_HEIGHT;
    dispDrv_.ver_res = TFT_WIDTH;
    dispDrv_.flush_cb = &Gui::flush;
    dispDrv_.draw_buf = &drawBuf_;
    lv_disp_drv_register(&dispDrv_);
    lv_png_init();
}

void Gui::runTask() {
    ITask::createTask("gui", &guiTask_);
    ITask::createTask("windowUpdate", &windowUpdateTask_);
}
