#include <Adafruit_GFX.h> 
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>
#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

// most mcufriend shields use these pins and Portrait mode:
uint8_t YP = A1;  // must be an analog pin, use "An" notation!
uint8_t XM = A2;  // must be an analog pin, use "An" notation!
uint8_t YM = 7;   // can be a digital pin
uint8_t XP = 6;   // can be a digital pin
uint8_t SwapXY = 0;

uint16_t TS_LEFT = 920;
uint16_t TS_RT  = 150;
uint16_t TS_TOP = 940;
uint16_t TS_BOT = 120;
char *name = "Unknown controller";
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 20
#define MAXPRESSURE 1000

#define SWAP(a, b) {uint16_t tmp = a; a = b; b = tmp;}

uint16_t identifier, oldcolor, currentcolor;
uint8_t Orientation = 1;    // 0-PORTRAIT, 1=LANDSCAPE
int x_coord,y_coord;

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//ASSIGN PAGE IDs

#define HOMESCREEN_PAGE 1
#define CALIBRATION_PAGE 2
#define MANUAL_CONTROL_PAGE 3
int currentPage,previousPage;

bool wait=true;


void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
    uint16_t tmp;
    
    tft.begin(9600);

    tft.reset();
    

    identifier = tft.readID();
    //    if (identifier == 0) identifier = 0x9341;
    if (0) {
    } else if (identifier == 0x0154) {
        name = "S6D0154";
        TS_LEFT = 914; TS_RT = 181; TS_TOP = 957; TS_BOT = 208;
    } else if (identifier == 0x7783) {
        name = "ST7781";
        TS_LEFT = 865; TS_RT = 155; TS_TOP = 942; TS_BOT = 153;
        SwapXY = 1;
    } else if (identifier == 0x7789) {
        name = "ST7789V";
        YP = A2; XM = A1; YM = 7; XP = 6;
        TS_LEFT = 906; TS_RT = 169; TS_TOP = 161; TS_BOT = 919;
    } else if (identifier == 0x9320) {
        name = "ILI9320";
        YP = A3; XM = A2; YM = 9; XP = 8;
        TS_LEFT = 902; TS_RT = 137; TS_TOP = 941; TS_BOT = 134;
    } else if (identifier == 0x9325) {
        name = "ILI9325";
        TS_LEFT = 900; TS_RT = 103; TS_TOP = 96; TS_BOT = 904;
    } else if (identifier == 0x9325) {
        name = "ILI9325 Green Dog";
        TS_LEFT = 900; TS_RT = 130; TS_TOP = 940; TS_BOT = 130;
    } else if (identifier == 0x9327) {
        name = "ILI9327";
        TS_LEFT = 899; TS_RT = 135; TS_TOP = 935; TS_BOT = 79;
        SwapXY = 1;
    } else if (identifier == 0x9329) {
        name = "ILI9329";
        TS_LEFT = 143; TS_RT = 885; TS_TOP = 941; TS_BOT = 131;
        SwapXY = 1;
    } else if (identifier == 0x9341) {
        name = "ILI9341 BLUE";
        TS_LEFT = 920; TS_RT = 139; TS_TOP = 944; TS_BOT = 150;
        SwapXY = 0;
    } else if (identifier == 0) {
        name = "ILI9341 DealExtreme";
        TS_LEFT = 893; TS_RT = 145; TS_TOP = 930; TS_BOT = 135;
        SwapXY = 1;
    } else if (identifier == 0 || identifier == 0x9341) {
        name = "ILI9341";
        TS_LEFT = 128; TS_RT = 911; TS_TOP = 105; TS_BOT = 908;
        SwapXY = 1;
    } else if (identifier == 0x9486) {
        name = "ILI9486";
        TS_LEFT = 904; TS_RT = 170; TS_TOP = 950; TS_BOT = 158;
//       TS_LEFT = 920; TS_RT = 150; TS_TOP = 940; TS_BOT = 120;
    } else if (identifier == 0x9488) {
        name = "ILI9488";
        TS_LEFT = 904; TS_RT = 170; TS_TOP = 950; TS_BOT = 158;
    } else if (identifier == 0xB509) {
        name = "R61509V";
        TS_LEFT = 889; TS_RT = 149; TS_TOP = 106; TS_BOT = 975;
        SwapXY = 1;
    } else {
        name = "unknown";
    }
    switch (Orientation) {      // adjust for different aspects
        case 0:   break;        //no change,  calibrated for PORTRAIT
        case 1:   tmp = TS_LEFT, TS_LEFT = TS_BOT, TS_BOT = TS_RT, TS_RT = TS_TOP, TS_TOP = tmp;  break;
        case 2:   SWAP(TS_LEFT, TS_RT);  SWAP(TS_TOP, TS_BOT); break;
        case 3:   tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;  break;
    }

    
    ts = TouchScreen(XP, YP, XM, YM, 300);     //call the constructor AGAIN with new values.
    tft.begin(identifier);
    tft.setRotation(Orientation);
    tft.fillScreen(BLUE);
 
    startPage();
}

void loop() {
  // put your main code here, to run repeatedly:

    tp=ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);
  if(tp.z>MINPRESSURE && tp.z<MAXPRESSURE){  
    if (SwapXY != (Orientation & 1)) SWAP(tp.x, tp.y);
   x_coord=map(tp.x,TS_RT,TS_LEFT,0,tft.width());
   y_coord=map(tp.y,TS_BOT,TS_TOP,0,tft.height());

//    x_coord=tp.x;
//    y_coord=tp.y;
  Serial.print("X_COORD: ");
  Serial.print(x_coord);
  Serial.print("  ");
  Serial.print("Width: ");
  Serial.print(tft.width());
  Serial.print("  ");
  Serial.print("Y_COORD: ");
  Serial.print( y_coord);
  Serial.print("  ");
  Serial.println(tft.height());
  check_btn_pressed(currentPage);
   }
  if(currentPage==HOMESCREEN_PAGE){
    dispTemp(27.56);
  }

   
}
