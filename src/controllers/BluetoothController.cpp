#include "BluetoothController.h"

#define BLUETOOTH_NAME "ESP32"

std::function<void (esp_spp_cb_event_t, esp_spp_cb_param_t *)> BluetoothController::onCallback;

void BluetoothController::init() {
    connected_ = false;
    using std::placeholders::_1;
    using std::placeholders::_2;
    onCallback = std::bind(&BluetoothController::callbackInner, this, _1, _2);
    serial_.begin(BLUETOOTH_NAME);
    serial_.register_callback(BluetoothController::callback);
}

void BluetoothController::run() {
    window_.load();
}

void BluetoothController::callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
    onCallback(event, param);
}

void BluetoothController::callbackInner(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
    if(event == ESP_SPP_SRV_OPEN_EVT) {
        Serial.println("Client connected");
        setConnection(true);
    } else if(event == ESP_SPP_CLOSE_EVT) {
        Serial.println("Client disconnected");
        setConnection(false);
    } else if(event == ESP_SPP_DATA_IND_EVT) {
        std::string received;
        while(serial_.available()) {
            received.push_back(serial_.read());
        }
        if(onReceive)
            onReceive(received);
    }
}

void BluetoothController::sendData(uint8_t* buf, int size) {
    if(connected_) {
        serial_.write(buf, size);
    }
}

void BluetoothController::setConnection(bool value) {
    connected_ = value;
    if(onConnectionChanged) {
        onConnectionChanged(connected_);
    }
}