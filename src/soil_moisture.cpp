#include <Arduino.h>
#include "lib/config.h"
#include "lib/soil_moisture.h"

int  soil_moisture_percentage(){

    int analogOutput =  analogRead(SOIL_MOISTURE_SENSOR);
    int soil_percentage = map(analogOutput, dry_value, wet_value, 0, 100);
    soil_percentage = constrain(soil_percentage, 0, 100); 
    return soil_percentage;

}