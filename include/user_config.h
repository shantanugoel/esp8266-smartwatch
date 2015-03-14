#ifndef _USER_CONFIG_H_
#define _USER_CONFIG_H_
#include "user_interface.h"

#define CFG_HOLDER	0x00FF55A1
#define CFG_LOCATION	0x3C

#define MQTT_HOST	"q.thingfabric.com" //or "mqtt.domain.com
#define MQTT_PORT	1883
#define MQTT_BUF_SIZE	1024
#define MQTT_KEEPALIVE		50	 /*second*/

#define MQTT_CLIENT_ID		"ESP8266_%8X"
#define MQTT_USER		"MQTTUSER"
#define MQTT_PASS		"MQTTPASS"
#define MQTT_SUB_TOPIC_NUM	1

#define AP_SSID "DVES_%08X"
#define AP_PASS "dves"
#define AP_TYPE AUTH_OPEN

#define STA_SSID "ssid"  // WIFI SSID
#define STA_PASS "pwd" // WIFI PASSWORD
#define STA_TYPE AUTH_WPA2_PSK

#define MQTT_RECONNECT_TIMEOUT 5
#define MQTT_CONNTECT_TIMER 5

#define DEFAULT_SECURITY	0
#define QUEUE_BUFFER_SIZE		 		2048
#define PROTOCOL_NAMEv31	/*MQTT version 3.1 compatible with Mosquitto v0.15*/
//PROTOCOL_NAMEv311			/*MQTT version 3.11 compatible with https://eclipse.org/paho/clients/testing/*/

#endif
