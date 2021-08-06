#include "MainWindow.h"

void MainWindow::load() {
    lv_obj_clean(lv_scr_act());
    label_ = lv_label_create(lv_scr_act());
    lv_obj_align(label_, LV_ALIGN_CENTER, 0, 0);
    needUpdate_ = true;
    onLoaded(this);
}

void MainWindow::setModel(MainModel *model) {
    model_ = model;
    model_->onUpdate = [=] {
        needUpdate_ = true;
    };
}

void MainWindow::update() {
    if(!model_ || !needUpdate_) {
        return;
    }
    Serial.printf("update MainWindow 222 %d\r\n", model_->getA());
    lv_label_set_text(label_, model_->getTest().c_str());
    needUpdate_ = false;
}