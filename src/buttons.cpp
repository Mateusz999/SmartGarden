#include "lib/buttons.h"
#include "lib/config.h"
#include <Arduino.h>

void init_buttons(){

    pinMode(BUTTON_BACK,INPUT_PULLUP);
    pinMode(BUTTON_OK,INPUT_PULLUP);
    pinMode(BUTTON_MENU,INPUT_PULLUP);


}