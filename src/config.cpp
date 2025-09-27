#include "lib/config.h"
#include <Arduino.h>

const char* percentage[] = {
  "95", "90", "85", "75", "70", "65", "60", "55", "50", "40", "35"
};

const char* timing[] = {
    "300","240","180","120","90","60","30"
};

const int percentage_length = sizeof(percentage) / sizeof(percentage[0]);
const int timing_length = sizeof(timing)/ sizeof(timing[0]);

int soil_moisture_sensitivity = 50;
int timer_setting = 30;
int soil_moisture_value = 100;

int dry_value = 4095;
int wet_value = 1300;

void init_params(int value,int time){
    soil_moisture_sensitivity =value;
    timer_setting = time;
    pinMode(RELAY_MODULE,OUTPUT);
    digitalWrite(RELAY_MODULE, HIGH);
    pinMode(SOIL_MOISTURE_SENSOR, INPUT);


}