#pragma once

#include "MainWindow.h"
#include <BluetoothSerial.h>
#include <string>
#include <functional>
#include "common.h"

class BluetoothController {
public:
    void init();
    void run();
    void sendData(uint8_t* buf, int size);
    std::function<void (bool)> onConnectionChanged;
    std::function<void ()> onTestChanged;
private:
    MainWindow mainWindow_;
    BluetoothSerial serial_;
    bool connected_;
    static std::function<void (esp_spp_cb_event_t, esp_spp_cb_param_t *)> onCallback;
    static void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);
    void setConnection(bool); 
    void callbackInner(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);
};