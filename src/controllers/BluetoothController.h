#pragma once

#include "../MainWindow.h"
#include <BluetoothSerial.h>
#include <string>

class BluetoothController {
public:
    void init();
    void run();
private:
    MainWindow mainWindow_;
    BluetoothSerial SerialBT_;
    bool connected_;
};