#pragma once

#include <functional>
#include <map>

class Slot {
public:
    static void add(std::function<void ()> *, std::function<void ()>);
    template <class T>
    static void add(std::function<void (T)> *, std::function<void (T)>);
    template <class T, class T2>
    static void add(std::function<void (T, T2)> *, std::function<void (T, T2)>);
    template <class T, class T2, class T3>
    static void add(std::function<void (T, T2, T3)> *, std::function<void (T, T2, T3)>);
};

template <class T>
void Slot::add(std::function<void (T)> *signal, std::function<void (T)> slot) {
    static std::multimap<std::function<void (T)> *, std::function<void (T)> > slots;
    slots.emplace(signal, slot);
    *signal = [=](T t) {
        for (auto itr = slots.find(signal); itr != slots.end(); itr++) {
            itr->second(t);
        }
    };
}

template <class T, class T2>
void Slot::add(std::function<void (T, T2)> *signal, std::function<void (T, T2)> slot) {
    static std::multimap<std::function<void (T, T2)> *, std::function<void (T, T2)> > slots;
    slots.emplace(signal, slot);
    *signal = [=](T t, T2 t2) {
        for (auto itr = slots.find(signal); itr != slots.end(); itr++) {
            itr->second(t, t2);
        }
    };
}

template <class T, class T2, class T3>
void Slot::add(std::function<void (T, T2, T3)> *signal, std::function<void (T, T2, T3)> slot) {
    static std::multimap<std::function<void (T, T2, T3)> *, std::function<void (T, T2, T3)> > slots;
    slots.emplace(signal, slot);
    *signal = [=](T t, T2 t2, T3 t3) {
        for (auto itr = slots.find(signal); itr != slots.end(); itr++) {
            itr->second(t, t2, t3);
        }
    };
}