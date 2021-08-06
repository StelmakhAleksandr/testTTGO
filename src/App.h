#pragma once

#include "Gui.h"
#include "ITask.h"
#include "FileSystem.h"
#include "BluetoothController.h"
#include "MainController.h"
#include "Slot.h"

class Test {
public: 
    int a;
};

class TestA : public ITask {
public:
    Test *test_;
    TestA(Test *test) {
        test_ = test;
    }
    void task() override {
        while(true) {
            test_->a++;
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
    }
};

class TestB : public ITask {
public:
    Test *test_;
    TestB(Test *test) {
        test_ = test;
    }
    void task() override {
        while(true) {
            Serial.printf("result a = %d\r\n", test_->a);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
};

class App {
public:
    void setup();
    void loop();
private:
    Gui gui_;
    FileSystem fileSystem_;
    BluetoothController bluetoothController_;
    MainController mainController_;

    Test a_;

    static void lvglPrint(const char *dsc);
    void initSignals();
};
