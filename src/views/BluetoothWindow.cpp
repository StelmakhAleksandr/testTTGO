#include "BluetoothWindow.h"

LV_IMG_DECLARE(bluetooth);

void BluetoothWindow::load() {
    lv_obj_clean(lv_scr_act());
    lv_obj_t *img = lv_img_create(lv_scr_act());
    lv_img_set_src(img, &bluetooth);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    onLoaded(this);
}

void BluetoothWindow::update() {
    
}