#include "FileSystem.h"

void FileSystem::init() {
    SPIFFS.begin();
    letter_ = 'S';
    lv_fs_drv_init(&drv_);                  
    drv_.letter = letter_;
    drv_.ready_cb = FileSystem::isReady;
    drv_.open_cb = FileSystem::fileOpen;
    drv_.close_cb = FileSystem::fileClose;
    drv_.read_cb = FileSystem::fileRead;
    drv_.write_cb = FileSystem::fileWrite;
    drv_.seek_cb = FileSystem::fileSeek;
    drv_.tell_cb = FileSystem::fileTell;

    drv_.dir_open_cb = FileSystem::dirOpen;
    drv_.dir_read_cb = FileSystem::dirRead;
    drv_.dir_close_cb = FileSystem::dirClose;   
    lv_fs_drv_register(&drv_);     

    // openFile(":/test.txt");
}

void FileSystem::openFile(std::string path) {
    path = letter_ + path;
    lv_fs_file_t f;
    lv_fs_res_t res;
    res = lv_fs_open(&f, path.c_str(), LV_FS_MODE_RD);
    if(res != LV_FS_RES_OK) {
        return;
    }

    uint32_t read_num;
    uint8_t buf[7];
    res = lv_fs_read(&f, buf, 7, &read_num);
    if(res != LV_FS_RES_OK || read_num != 7) {
        return;
    }

    Serial.printf("result = %s \r\n", (char*)buf);

    lv_fs_close(&f);
}

void FileSystem::showDir(std::string path) {
    path = letter_ + path;
    lv_fs_dir_t dir;
    lv_fs_res_t res;
    res = lv_fs_dir_open(&dir, path.c_str());
    if(res != LV_FS_RES_OK) 
        return;

    char fn[256];
    while(1) {
        res = lv_fs_dir_read(&dir, fn);
        if(res != LV_FS_RES_OK) {
            break;
        }

        /*fn is empty, if not more files to read*/
        if(strlen(fn) == 0) {
            break;
        }

        Serial.printf("%s\n", fn);
    }
    lv_fs_dir_close(&dir);
}

bool FileSystem::isReady(lv_fs_drv_t *drv) {
    return true;
}

void *FileSystem::fileOpen(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode) {
    Serial.printf("fileOpen %s \r\n", path);
    char *spiffsmode = FILE_READ;
    if(mode == LV_FS_MODE_WR)
        spiffsmode = FILE_WRITE;
    return new File(SPIFFS.open(path, spiffsmode));
}

lv_fs_res_t FileSystem::fileRead(lv_fs_drv_t *drv, void *fileP, void *buf, uint32_t bytesToRead, uint32_t *bytesRead) {
    File *file = static_cast<File*>(fileP);
    int result = file->read((uint8_t*)buf, bytesToRead);
    if(result == - 1) {
        return LV_FS_RES_UNKNOWN;
    }
    *bytesRead = result;
    return LV_FS_RES_OK;
}

lv_fs_res_t FileSystem::fileWrite(lv_fs_drv_t *drv, void * fileP, const void *buf, uint32_t btw, uint32_t *bw) {
    Serial.printf("fileWrite \r\n");
    return LV_FS_RES_UNKNOWN;
}

lv_fs_res_t FileSystem::fileSeek(lv_fs_drv_t *drv, void *fileP, uint32_t pos, lv_fs_whence_t whence) {
    File *file = static_cast<File*>(fileP);
    SeekMode mode;
    switch(whence) {
        case LV_FS_SEEK_SET: mode = SeekSet;
        break; 
        case LV_FS_SEEK_CUR: mode = SeekCur;
        break;
        case LV_FS_SEEK_END: mode = SeekEnd;
        break;
        default : break;
    }
    Serial.printf("file seek %d \r\n", pos);
    if(!file->seek(pos, mode)) {
        Serial.printf("file seek error %d \r\n", pos);
        return LV_FS_RES_UNKNOWN;
    }
    return LV_FS_RES_OK;
}

lv_fs_res_t FileSystem::fileTell(lv_fs_drv_t * drv, void * fileP, uint32_t *posP) {
    File *file = static_cast<File*>(fileP);
    *posP = file->position();
    return LV_FS_RES_OK;
}

lv_fs_res_t FileSystem::fileClose(lv_fs_drv_t *drv, void *fileP) {
    Serial.printf("file close \r\n");
    File *file = static_cast<File*>(fileP);
    file->close();
    delete file;
    return LV_FS_RES_OK;
}

void *FileSystem::dirOpen(lv_fs_drv_t *drv, const char *path) {
    return new File(SPIFFS.open(path));
}

lv_fs_res_t FileSystem::dirRead(lv_fs_drv_t *drv, void *dirP, char *fileName) {
    File *dir = static_cast<File*>(dirP);
    File file = dir->openNextFile();
    if(file) {
        strcpy(fileName, file.name());
        return LV_FS_RES_OK;
    } 
    return LV_FS_RES_UNKNOWN;
}

lv_fs_res_t FileSystem::dirClose(lv_fs_drv_t *drv, void *dirP) {
    File *dir = static_cast<File*>(dirP);
    dir->close();
    delete dir;
    return LV_FS_RES_OK;
}