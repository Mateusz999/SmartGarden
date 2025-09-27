
#include "lib/config.h"
#include "lib/display_modes.h"
#include "lib/oled.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>


Adafruit_SH1106 display(OLED_SDA, OLED_SCL);

extern int selectedMenuIndex;

void initOLED() {
  display.begin(SH1106_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Temperatura: " + String(temp) + " C");
  display.setCursor(0, 14);
  display.println("Wilgotnosc: " + String(humidity) + " %");
  display.setCursor(0, 28);
  display.println("B:" + String(button_back) + " O:" + String(button_ok) + " M:" + String(button_menu));
  display.display();
}

void updateData(float temp, float humidity, int button_ok, int button_back, int button_menu,int soil_moi_val) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Temperatura: " + String(temp) + " C");
  display.setCursor(0, 14);
  display.println("Wilgotnosc: " + String(humidity) + " %");
  display.setCursor(0, 28);
  display.println("Gleba:" +String(soil_moi_val)+" %");
  display.println("czulosc:" +String(soil_moisture_sensitivity)+" %");
  display.println("czasowka:" +String(timer_setting)+" sek");
  display.display();
}

void showMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  String title = "-- Timer --";
  int textWidth = title.length() * 6; 
  int screenWidth = 128;            
  int x = (screenWidth - textWidth) / 2;

display.setCursor(x, 0);
display.println(title);
  int visible_items = 4;
  int scroll_offset = 0;
  if(selectedMenuIndex < scroll_offset){
    scroll_offset = selectedMenuIndex;
  } else if ( selectedMenuIndex >= scroll_offset + visible_items) {
    scroll_offset = selectedMenuIndex - visible_items + 1;
  }
  for(int j = 0;j<visible_items;j++){
    int idx  = scroll_offset + j;
    if(idx > timing_length) break;
    int y = 14 + j * 12;
    if(idx == selectedMenuIndex){
      display.fillRect(0,y,128,12,WHITE);
      display.setTextColor(BLACK);
    }else{
      display.setTextColor(WHITE);
    }
    display.setCursor(2, y);
    display.println(timing[idx]);
  }
  display.display();
}

void settingMenu(){

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Sensitivity[%]:");

  int visible_items = 4;
  int scroll_offset = 0;
  if(selectedMenuIndex < scroll_offset){
    scroll_offset = selectedMenuIndex;
  } else if ( selectedMenuIndex >= scroll_offset + visible_items) {
    scroll_offset = selectedMenuIndex - visible_items + 1;
  }

  for(int j = 0;j<visible_items;j++){
    int idx  = scroll_offset + j;
    if(idx > percentage_length) break;
    int y = 14 + j * 12;
    if(idx == selectedMenuIndex){
      display.fillRect(0,y,128,12,WHITE);
      display.setTextColor(BLACK);
    }else{
      display.setTextColor(WHITE);
    }
    display.setCursor(2, y);
    display.println(percentage[idx]);
  }
  display.display();

}