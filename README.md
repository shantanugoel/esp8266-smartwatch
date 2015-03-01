#esp8266-smartwatch
This project is by [Shantanu Goel](http://tech.shantanugoel.com/) for a smartwatch based on ESP8266. This software repository consists the following development:
* Modify and refactor Tuan PM's port of the [MQTT client library for ESP8266](https://github.com/tuanpmt/esp_mqtt)
* Use zarya's [I2C driver](https://github.com/zarya/esp8266_i2c_driver)
* Modify and refactor this [OLED driver](http://www.esp8266.com/viewtopic.php?p=4311#p4311)
* Add an NTP driver and a client

Thanks to [Nathan](https://github.com/nathanchantrell/esp_mqtt_oled) for the original code that combined the mqtt and oled drivers

The aim is to build an extensible smartwatch framework which is easily configurable

##Hardware
* ESP8266 (Developing currently on ESP-01 but others should be usable as is)
* A 0.96" 128x64 I2C OLED which is easily available from ebay or other electronic shops
* A 3.3v USB FTDI board for programming/powering the esp8266 and the oled during development. Will be replaced by a LIPO battery finally

##Current Status
* Subscribes to an MQTT topic and displays it on the OLED
 * Using this with tasker on phone and [ThingFabric](http://www.thingfabric.com) to send phone notifications to the watch
* Gets the current time from NTP server at boot up and displays on the OLED

##Changelog
Check commit history

##Configuration
* I2C address for the OLED is in include/driver/i2c_oled.h
* MQTT broker and WiFi settings are in include/user_config.h
* GPIO pins to use for I2C are in driver/i2c.h
* MQTT topics to subscribe to are in the MQTT_Start() function in user/mqtt.c
* What to do with the incoming messages is defined in deliver_publish() in user/mqtt.c
* NTP server IP address is in user/ntp.c

##TODO
* Decouple OLED code from ntp
* Build clock function on top of the ntp client to update display with latest time
* Refactor MQTT code and segregate wifi and ntp/clock management from it
* Refactor OLED code to better manage all the different writes ongoing and prevent a write wiping out other things on display
* Add framework to configure things for individual users without having to recompile the code
* Add watchfaces (wishlist)
* Add buttons support to take actions on the watch
* Add communication support from watch to phone
