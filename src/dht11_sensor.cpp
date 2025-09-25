#include "lib/dht11_sensor.h"
#include "lib/config.h"
#include <DHT.h>

DHT dht(DHTPIN, DHTTYPE);

void initDHT() {
  dht.begin();
}

float readTemperature() {
  return dht.readTemperature();
}

float readHumidity() {
  return dht.readHumidity();
}
