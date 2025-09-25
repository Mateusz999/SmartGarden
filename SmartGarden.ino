#include <Arduino.h>
#include "lib/config.h"
#include "lib/dht11_sensor.h"
#include "lib/oled.h"
#include "lib/buttons.h"
#include "lib/display_modes.h"

float temp = 22.0;
float humidity = 34.0;
int button_ok = 0;
int button_back = 0;
int button_menu = 0;
DisplayMode current_display_mode = MODE_DATA;
int selectedMenuIndex = 0;

bool lastMenuState = HIGH;

void setup() {
  Serial.begin(115200);
  initDHT();
  initOLED();
  init_buttons();
  init_params(50,30);
}

void loop() {
  button_ok = digitalRead(BUTTON_OK);
  button_back = digitalRead(BUTTON_BACK);
  button_menu = digitalRead(BUTTON_MENU);

  temp = readTemperature();
  humidity = readHumidity();

  if (button_back == LOW) {
    current_display_mode = MODE_DATA;
    delay(300);
  }

  switch (current_display_mode) {
    case MODE_DATA:
      if (lastMenuState == HIGH && button_menu == LOW) {
        current_display_mode = MODE_MENU;
        selectedMenuIndex = 0;
        showMenu();
        delay(300);
      } else if (lastMenuState == HIGH && button_ok == LOW) {
        current_display_mode = MODE_SETTINGS;
        selectedMenuIndex = 0;
        settingMenu();
        delay(300);
      } else {
        updateData(temp, humidity, button_ok, button_back, button_menu);
      }
      break;

    case MODE_MENU:
     if(button_ok == LOW){
      timer_setting = atoi(timing[selectedMenuIndex]);
      current_display_mode = MODE_DATA;
      } 
      if (lastMenuState == HIGH && button_menu == LOW) {
        selectedMenuIndex++;
        if (selectedMenuIndex >= timing_length) {
          selectedMenuIndex = 0;
        }
        showMenu();
        delay(300);
      } else {
        showMenu();
      }
      break;

    case MODE_SETTINGS:
    if(button_menu == LOW){
      soil_moisture_sensitivity = atoi(percentage[selectedMenuIndex]);
      current_display_mode = MODE_DATA;
    } 
      if (lastMenuState == HIGH && button_ok == LOW) {
        selectedMenuIndex++;
        if (selectedMenuIndex >= percentage_length) {
          selectedMenuIndex = 0;
        }
        settingMenu();
        delay(300);
      } else {
        settingMenu();
      }
      break;
  }

  lastMenuState = button_menu;
  delay(50);
}
