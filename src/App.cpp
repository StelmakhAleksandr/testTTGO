#include "App.h"

void App::setup() {
    Serial.begin(115200);
    lv_init();
    lv_log_register_print_cb(App::lvglPrint);
    gui_.init();
    fileSystem_.init();    

    bluetoothController_.init();

    ITask::createTask("gui", &gui_);
    std::function<void ()> func = std::bind(&App::test, this); 
    Slot::add(&bluetoothController_.onTestChanged, &func);

    bluetoothController_.run();
}

void App::loop() {
}

void App::lvglPrint(const char *dsc) {
    Serial.printf("%s \r\n", dsc);
}

void App::test() {
    Serial.println("APP::test");
    
}