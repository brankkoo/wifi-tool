#include <stdio.h>
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "freertos/FreeRTOS.h"
#include "esp_wifi_types.h"
#include "nvs_flash.h"
#include "sniff.h"
#define WIFI_CHANNEL_MAX (13)
#define DELAY_INTERVAL (500)



void app_main(void)
{
    wifi_sniffer_init();
    uint8_t channel = 1;
    while (true)
    {
        vTaskDelay(DELAY_INTERVAL);  
        esp_wifi_set_channel(channel,WIFI_SECOND_CHAN_NONE);
        // if(channel <= WIFI_CHANNEL_MAX){
        //     channel++;
        // }
        // else{
        //     channel = 0;
        // }
    }
}



