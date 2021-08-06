#include "App.h"

void App::setup() {
    Serial.begin(115200);
    lv_init();
    lv_log_register_print_cb(App::lvglPrint);
    gui_.init();
    fileSystem_.init();    
    bluetoothController_.init();
    mainController_.init();

    initSignals();
    bluetoothController_.run();
    gui_.runTask();

    TestA *testA = new TestA(&a_);
    TestB *testB = new TestB(&a_);

    // ITask::createTask("testA", testA);
    // ITask::createTask("testB", testB);

    a_.a = 145;

    mainController_.setText("pzdc");
}

void App::loop() {
}

void App::lvglPrint(const char *dsc) {
    Serial.printf("%s \r\n", dsc);
}

void App::initSignals() {
    using std::placeholders::_1;
    using std::placeholders::_2;
    // Slot::add(&bluetoothController_.onConnectionChanged, (std::function<void (bool)>)std::bind(&App::blt, this, _1));
    bluetoothController_.onConnectionChanged = [=](bool connected) {
        if(connected) {
            mainController_.run();
        } else {
            bluetoothController_.run();
        }
    };

    bluetoothController_.onReceive = std::bind(&MainController::setText, mainController_, _1);
}