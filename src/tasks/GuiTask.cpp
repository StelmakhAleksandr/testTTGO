#include "GuiTask.h"

void GuiTask::task() {
    while(true) {
        lv_timer_handler(); 
        lv_tick_inc(5);
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}