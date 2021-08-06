#include "MainModel.h"

std::string MainModel::getTest() {
    Serial.printf("model get %s \r\n", test_.c_str());
    return test_;
}

void MainModel::setTest(std::string test) {
    setA(45);
    test_ = test;
    Serial.printf("update model %s \r\n", test_.c_str());
    update();
}

void MainModel::update() {
    if(onUpdate) {
        onUpdate();
    }
}

int MainModel::getA() {
    return a_;
}

void MainModel::setA(int a) {
    a_ = a;
    update();
}