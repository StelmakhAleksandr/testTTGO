#include "MainController.h"

void MainController::init() {
    window_.setModel(&model_);
    model_.setTest("START");
    model_.setA(10);
}

void MainController::run() {
    window_.load();
}

void MainController::setText(std::string text) {
    model_.setTest(text);
}