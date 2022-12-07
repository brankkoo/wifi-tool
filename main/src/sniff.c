#include "sniff.h"
#include <stdio.h>
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_wifi_types.h"
#include "nvs_flash.h"

typedef struct{
    unsigned frame_ctrl:16;
    unsigned duration_id:16;
    uint8_t addr1[6];
    uint8_t addr2[6];
    uint8_t addr3[6];
    unsigned sequence_ctrl:16;
    uint8_t addr4[6];
}mac_header_t;

typedef struct {
	mac_header_t hdr;
	uint8_t payload[0]; 
} wifi_ieee80211_packet_t;

void packet_handler(void *buf, wifi_promiscuous_pkt_type_t type){
if(type != WIFI_PKT_MGMT)
    return;
const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t *) buf;
const wifi_ieee80211_packet_t *pkt = ppkt->payload;
mac_header_t *header = &pkt->hdr;
uint8_t *data = &pkt->payload;
printf("channel = %02d, rssi = %02d",ppkt->rx_ctrl.channel
,ppkt->rx_ctrl.rssi);
printf(" reciver adress=%02x:%02x:%02x:%02x:%02x:%02x,"
		" sender adress=%02x:%02x:%02x:%02x:%02x:%02x,"
		" filter adress=%02x:%02x:%02x:%02x:%02x:%02x\n" 
,header->addr1[0]
,header->addr1[1]
,header->addr1[2]
,header->addr1[3]
,header->addr1[4]
,header->addr1[5]
,header->addr2[0]
,header->addr2[1]
,header->addr2[2]
,header->addr2[3]
,header->addr2[4]
,header->addr2[5]
,header->addr3[0]
,header->addr3[1]
,header->addr3[2]
,header->addr3[3]
,header->addr3[4]
,header->addr3[5]);


printf(" Data : %s", data);
}

void wifi_sniffer_init(){
    nvs_flash_init();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_mode(WIFI_MODE_NULL);
    esp_wifi_start();
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb(&packet_handler);
}