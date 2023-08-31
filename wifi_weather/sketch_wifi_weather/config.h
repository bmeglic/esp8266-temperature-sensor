#define CFG_WIFI_AP   "xx"
#define CFG_WIFI_PASSWORD   "xxxxxxxx"

#define CFG_MQTT_IP   "192.168.xxx.xxx"
#define CFG_MQTT_PORT 1883
#define CFG_MQTT_USERNAME "xxxxx"
#define CFG_MQTT_PASSWORD "xxxxx"
#define CFG_MQTT_CLIENT_ID  "sensor1"
#define CFG_MQTT_TOPIC  "sensors/" CFG_MQTT_CLIENT_ID

#define CFG_SHT11_PIN_SDA 0
#define CFG_SHT11_PIN_SCK 2
#define CFG_MEASURE_INTERVAL 300e6

#define CFG_MEASURE_TEMPERATURE_CALIBRATION (0.0)
#define CFG_MEASURE_HUMIDITY_CALIBRATION    (-5.0)
