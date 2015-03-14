#include "ets_sys.h"
#include "driver/uart.h"
#include "osapi.h"
#include "mqtt.h"
#include "config.h"
#include "debug.h"
#include "gpio.h"
#include "user_interface.h"
#include "os_type.h"
#include "user_config.h"
#include "mem.h"
#include "driver/uart_register.h"
#include "driver/uart.h"
#include "driver/i2c.h"
#include "driver/i2c_oled.h"

extern void ets_wdt_disable(void);

static volatile bool OLED;
MQTT_Client mqttClient;

void wifiConnectCb(uint8_t status)
{
  if(status == STATION_GOT_IP){
    MQTT_Connect(&mqttClient);
  } else {
    MQTT_Disconnect(&mqttClient);
  }
}
void mqttConnectedCb(uint32_t *args)
{
  MQTT_Client* client = (MQTT_Client*)args;
  INFO("MQTT: Connected\r\n");
  MQTT_Subscribe(client, "/mqtt/topic/0", 0);
  MQTT_Subscribe(client, "/mqtt/topic/1", 1);
  MQTT_Subscribe(client, "/mqtt/topic/2", 2);

  MQTT_Publish(client, "/mqtt/topic/0", "hello0", 6, 0, 0);
  MQTT_Publish(client, "/mqtt/topic/1", "hello1", 6, 1, 0);
  MQTT_Publish(client, "/mqtt/topic/2", "hello2", 6, 2, 0);

}

void mqttDisconnectedCb(uint32_t *args)
{
  MQTT_Client* client = (MQTT_Client*)args;
  INFO("MQTT: Disconnected\r\n");
}

void mqttPublishedCb(uint32_t *args)
{
  MQTT_Client* client = (MQTT_Client*)args;
  INFO("MQTT: Published\r\n");
}

void mqttDataCb(uint32_t *args, const char* topic, uint32_t topic_len, const char *data, uint32_t data_len)
{
  char *topicBuf = (char*)os_zalloc(topic_len+1),
       *dataBuf = (char*)os_zalloc(data_len+1);

  MQTT_Client* client = (MQTT_Client*)args;

  os_memcpy(topicBuf, topic, topic_len);
  topicBuf[topic_len] = 0;

  os_memcpy(dataBuf, data, data_len);
  dataBuf[data_len] = 0;

  INFO("Receive topic: %s, data: %s \r\n", topicBuf, dataBuf);
  os_free(topicBuf);
  os_free(dataBuf);
}


void user_init(void)
{
  uart_init(BIT_RATE_115200, BIT_RATE_115200);
  os_delay_us(1000000);

  i2c_init();
  OLED = OLED_Init();

  OLED_Print(2, 0, "ESP8266 SMARTWATCH", 1);

  CFG_Load();

  MQTT_InitConnection(&mqttClient, sysCfg.mqtt_host, sysCfg.mqtt_port, sysCfg.security);
  //MQTT_InitConnection(&mqttClient, "192.168.11.122", 1880, 0);

  MQTT_InitClient(&mqttClient, sysCfg.device_id, sysCfg.mqtt_user, sysCfg.mqtt_pass, sysCfg.mqtt_keepalive, 1);
  //MQTT_InitClient(&mqttClient, "client_id", "user", "pass", 120, 1);

  MQTT_InitLWT(&mqttClient, "/lwt", "offline", 0, 0);
  MQTT_OnConnected(&mqttClient, mqttConnectedCb);
  MQTT_OnDisconnected(&mqttClient, mqttDisconnectedCb);
  MQTT_OnPublished(&mqttClient, mqttPublishedCb);
  MQTT_OnData(&mqttClient, mqttDataCb);

  WIFI_Connect(sysCfg.sta_ssid, sysCfg.sta_pwd, wifiConnectCb);

  INFO("\r\nSystem started ...\r\n");
}
