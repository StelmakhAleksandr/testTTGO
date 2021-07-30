#pragma once

#include <functional>

#define PROPERTY(type, var)  private: type var; \
    public: type get_##var() const { return var; } \
    std::function<void (type)> var##_changed(); \
    void set_##var(type val) { var = val; if(var##_changed) var##_changed();}