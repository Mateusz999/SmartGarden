#pragma once
#include "display_modes.h"
extern float temp;
extern float humidity;
extern int button_ok;
extern int button_back;
extern int button_menu;
extern int relay_module_state;
#define DHTPIN 18
#define DHTTYPE DHT11

#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_ADDR 0x3C

#define BUTTON_BACK 23
#define BUTTON_OK 19
#define BUTTON_MENU 4

#define SOIL_MOISTURE_SENSOR 15

#define RELAY_MODULE 2

extern const char* percentage[];
extern const int percentage_length;

extern const char* timing[];
extern const int timing_length;

extern int soil_moisture_sensitivity;
extern int timer_setting;

extern int dry_value;
extern int wet_value;

extern int soil_moisture_value;
void init_params(int value,int time);