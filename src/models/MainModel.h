#pragma once

#include <Arduino.h>
#include <string>
#include <functional>

class MainModel {
public:
    int getA();
    void setA(int a);
    std::function<void ()> onUpdate;
    void setTest(std::string test);
    std::string getTest();
    
private:
    std::string test_;
    int a_;
    void update();
};