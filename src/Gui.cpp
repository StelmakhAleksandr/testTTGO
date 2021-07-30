#include "Gui.h"

TFT_eSPI GUI::tft_;

void GUI::flush(_lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    tft_.startWrite();
    tft_.setAddrWindow( area->x1, area->y1, w, h );
    tft_.pushColors((uint16_t*)&color_p->full, w * h, true);
    tft_.endWrite();
    lv_disp_flush_ready(disp);
}

void GUI::init() {
    tft_.begin();
    tft_.setRotation(1); 
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, TFT_WIDTH * 10);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = TFT_HEIGHT;
    disp_drv.ver_res = TFT_WIDTH;
    disp_drv.flush_cb = &GUI::flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    lv_png_init();
}

void GUI::task() {
    while(true) {
        lv_timer_handler(); 
        lv_tick_inc(5);
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}
