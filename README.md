# Description

Sketch for ESP-32 used to physically toggle PC power switch when signaled over the MQTT protocol

## Create header file
Missing header file (src/cred.h) must be written like so:
```
#define WIFI_SSID "ssid"
#define WIFI_PASSWORD "pass"
#define MQTT_SERVER "broker.com"
#define MQTT_PORT 1234
#define MQTT_USER "user"
#define MQTT_PASSWORD "pass"
#define MQTT_SUB_TOPIC "/toggle-power"
#define MQTT_MESSAGE "true"
```
## Activating support for ESP-32 in Arduino IDE

* Add additional board manager URL in preferences:```https://dl.espressif.com/dl/package_esp32_index.json```

* Search and install ESP32 by Espressif Systems


## Dependencies

* **PubSubClient**. This library can be installed from Library manager

* **pyserial**. Install pyserial using pip like ```pip install pyserial```
