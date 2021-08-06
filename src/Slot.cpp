#include "Slot.h"

void Slot::add(std::function<void ()> *signal, std::function<void ()> slot) {
    static std::multimap<std::function<void ()> *, std::function<void ()> > slots;
    slots.emplace(signal, slot);
    *signal = [=]() {
        for (auto itr = slots.find(signal); itr != slots.end(); itr++) {
            itr->second();
        }
    };
}