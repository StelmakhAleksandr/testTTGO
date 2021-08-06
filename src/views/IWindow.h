#pragma once

#include <functional>

class IWindow {
public:
    virtual void update() = 0;
    virtual void load() = 0;
    IWindow();
protected:
    bool needUpdate_;
    std::function<void (IWindow*)> onLoaded;
};