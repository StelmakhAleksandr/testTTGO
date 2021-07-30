#pragma once

#include <lvgl.h>
#include "SPIFFS.h"
#include <Arduino.h>
#include <string>

class FileSystem {
public:
    void init();
    void showDir(std::string path);
    void openFile(std::string path);
private:
    lv_fs_drv_t drv_;
    char letter_;
    static bool isReady(lv_fs_drv_t *);
    static void *fileOpen(lv_fs_drv_t *, const char *, lv_fs_mode_t);
    static lv_fs_res_t fileRead(lv_fs_drv_t *, void *, void *, uint32_t, uint32_t *);
    static lv_fs_res_t fileWrite(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw);
    static lv_fs_res_t fileSeek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence);
    static lv_fs_res_t fileTell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p);
    static lv_fs_res_t fileClose(lv_fs_drv_t *, void *);
    static void *dirOpen(lv_fs_drv_t *, const char *);
    static lv_fs_res_t dirRead(lv_fs_drv_t *, void *, char *);
    static lv_fs_res_t dirClose(lv_fs_drv_t *, void *);
};