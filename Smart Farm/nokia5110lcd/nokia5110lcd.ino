#include "U8glib.h"

U8GLIB_PCD8544 u8g(8, 4, 7, 5, 6);  // CLK=8, DIN=4, CE=7, DC=5, RST=6
#define backlight_pin 11

void setup(void) {
  analogWrite(backlight_pin, 50);  /* Set the Backlight intensity */
}


void draw() {
 
  u8g.setFont(u8g_font_profont11);  // select font
  u8g.drawStr(0, 15, "Smart Farm");  // put string of display at position X, Y
  //u8g.drawStr(29, 35, "HELLO!!!!");
  
  
}

void loop(void) {
u8g.firstPage(); 
  do {
    draw();
  } while( u8g.nextPage() ); 

}
