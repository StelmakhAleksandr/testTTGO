#include "BluetoothController.h"

void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
    if(event == ESP_SPP_SRV_OPEN_EVT) {
        Serial.println("Client Connected");
        // connected_ = true;
    } else if(event == ESP_SPP_CLOSE_EVT) {
        Serial.println("Client disconnected");
        // connected_ = false;
    }
}

void BluetoothController::init() {
    SerialBT_.begin("ESP32");
    SerialBT_.register_callback(callback);
}

void BluetoothController::run() {
    mainWindow_.load();

    // Serial.println("hello");
    // std::string value = "yeah";
    // if(connected) {
    //     SerialBT.write((const uint8_t*)value.c_str(), value.size());
    // }
    // delay(1000);
}