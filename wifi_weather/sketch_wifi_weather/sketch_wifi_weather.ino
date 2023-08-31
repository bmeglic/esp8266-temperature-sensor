
#include <ESP8266WiFi.h>
#include <ArduinoMqttClient.h>
#include <SHT1x.h>

#include "config.h"

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
SHT1x sht1x(CFG_SHT11_PIN_SDA, CFG_SHT11_PIN_SCK);

bool init_wifi(void)
{
  int retries = 50;

  WiFi.begin(CFG_WIFI_AP, CFG_WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");

    retries--;
    if (retries == 0) {
      return false;
    }
  }

  return true;
}

bool connect_to_mqtt(void)
{
  int retries = 5;

  while (true) {

    mqttClient.setConnectionTimeout(1000);
    mqttClient.setUsernamePassword(CFG_MQTT_USERNAME, CFG_MQTT_PASSWORD);
    mqttClient.setId(CFG_MQTT_CLIENT_ID);

    if (mqttClient.connect(CFG_MQTT_IP, CFG_MQTT_PORT) == true) {
      Serial.println("Connected to MQTT broker");
      return true;
    }

    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    retries--;
    if (retries == 0) {
      return false;
    }
  }

  return false;
}

void go_to_sleep(void)
{
  mqttClient.stop();
  WiFi.disconnect();
  ESP.deepSleep(CFG_MEASURE_INTERVAL);
}

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Initializing sensor: " CFG_MQTT_CLIENT_ID));

  float temperature = sht1x.readTemperatureC() + CFG_MEASURE_TEMPERATURE_CALIBRATION;
  float humidity = sht1x.readHumidity() + CFG_MEASURE_HUMIDITY_CALIBRATION;
  Serial.printf("Temperature: %.2f, Humidity: %.0f", temperature, humidity);
  Serial.println();

  if (init_wifi() != true) {
    Serial.println("Failed to connect to WiFi AP");
    go_to_sleep();
  }

  if (connect_to_mqtt() != true) {
    Serial.println("Failed to connect to MQTT broker");
    go_to_sleep();
  }

  mqttClient.beginMessage(CFG_MQTT_TOPIC);
  mqttClient.printf("{ \"temperature\": %f, \"humidity\": %f }", temperature, humidity);
  mqttClient.endMessage();

  go_to_sleep();
}

void loop()
{
  delay(1000);
  go_to_sleep();
}
