# esp8266-temperature-sensor
Temperature &amp; humidity sensor based on Arduino &amp; ESP8266 &amp; SHT11


Arduino application runs on the ESP8266. It is capable of reading temperature
and humidity levels from the sensor SHT11, and applying calibration based on
configuration.

It then connects to the Wifi AP, connects to the MQTT server and sends the
measurements to the MQTT topic.

After that it goes to deep sleep to preseve battery power. It can run directly
out of 2x AA Ni-Mh rechargeable batteries for a couple of months without
recharging.


## Configuration

Configuration is done by editing the `wifi_weather/sketch_wifi_weather/config.h`
file.
