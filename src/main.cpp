#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "TAMC_GT911.h"


#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 480
#define GFX_BL 2
Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
  40,  // DE
  41,  // VSYNC
  39,  // HSYNC
  42,  // PCLK
  45,  // R0
  48,  // R1
  47,  // R2
  21,  // R3
  14,  // R4
  5 ,  // G0
  6 ,  // G1
  7 ,  // G2
  15,  // G3
  16,  // G4
  4 ,  // G5
  8 ,  // B0
  3 ,  // B1
  46,  // B2
  9 ,  // B3
  1 ,  // B4
  0 ,  // hsync_polarity 
  8 ,  // hsync_front_porch 
  4 ,  // hsync_pulse_width
  8 ,  // hsync_back_porch
  0 ,  // vsync_polarity
  8 ,  // vsync_front_porch 
  4 ,  // vsync_pulse_width
  8 ); // vsync_back_porch

Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
  SCREEN_WIDTH,    // width 
  SCREEN_HEIGHT,    // height
  rgbpanel, 
  0,      // rotation 
  true);  // auto_flush

//************************************************************************************************************

#define TOUCH_SDA 19
#define TOUCH_SCL 20
#define TOUCH_INT 35 //unused pin
#define TOUCH_RST 38
#define TOUCH_WIDTH 480
#define TOUCH_HEIGHT 272

TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);

//************************************************************************************************************

void setup() {
  Serial.begin(115200);
  Serial.println("TAMC_GT911 Example: Ready");
  tp.begin();
  tp.setRotation(ROTATION_NORMAL);
}

void loop() {
  tp.read();
  if (tp.isTouched){
    for (int i=0; i<tp.touches; i++){
      Serial.print("Touch ");Serial.print(i+1);Serial.print(": ");;
      Serial.print("  x: ");Serial.print(tp.points[i].x);
      Serial.print("  y: ");Serial.print(tp.points[i].y);
      Serial.print("  size: ");Serial.println(tp.points[i].size);
      Serial.println(' ');
    }
  }
}
