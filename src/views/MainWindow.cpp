#include "MainWindow.h"
#include <string>

LV_IMG_DECLARE(bluetooth);

void MainWindow::load() {
    
    // lv_obj_t * img = lv_gif_create_from_data(lv_scr_act(), test_map);
    // lv_obj_t * img = lv_gif_create_from_file(lv_scr_act(), "S:/test5.gif");
    lv_obj_t * img = lv_img_create(lv_scr_act());
    // lv_img_set_src(img, "S:/123.png");
    lv_img_set_src(img, &bluetooth);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
}
