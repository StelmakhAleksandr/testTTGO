#pragma once

#include "Gui.h"
#include "ITask.h"
#include "FileSystem.h"
#include "BluetoothController.h"

class App {
public:
    void setup();
    void loop();
private:
    GUI gui_;
    FileSystem fileSystem_;
    BluetoothController bluetoothController_;

    static void lvglPrint(const char *dsc);
};
