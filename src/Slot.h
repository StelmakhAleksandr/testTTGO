#pragma once

#include <functional>
#include <map>
#include <vector>
#include <Arduino.h>

class Slot {
public:
    static void add(std::function<void ()> *signal, std::function<void ()> *slot) {
        *signal = std::bind(Slot::test, signal);
        slots_.emplace(signal, slot);
    }
private:
    static std::multimap<void *, void *> slots_;
    static void test(void *signal) {
        Serial.println("Slot::test");
        for (auto itr = slots_.find(signal); itr != slots_.end(); itr++) {
            std::function<void ()> *func = static_cast<std::function<void ()> *>(itr->second);
            (*func)();
        }
    }
};