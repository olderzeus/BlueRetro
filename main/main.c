#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sd.h"
#include "nsi.h"
#include "maple.h"
#include "bt_host.h"
#include "config.h"

static void wired_init_task(void *arg) {
    //nsi_init(NSI_CH, 26, NSI_SLAVE, &output[0]);
    //init_maple(&output[0]);
    vTaskDelete(NULL);
}

static void wl_init_task(void *arg) {
    if (sd_init()) {
        printf("SD init fail!\n");
    }

    config_init();

    if (bt_host_init()) {
        printf("Bluetooth init fail!\n");
    }
    vTaskDelete(NULL);
}

void app_main()
{
    xTaskCreatePinnedToCore(wl_init_task, "wl_init_task", 2048, NULL, 10, NULL, 0);
    xTaskCreatePinnedToCore(wired_init_task, "wired_init_task", 2048, NULL, 10, NULL, 1);
}

