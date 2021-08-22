void draw_ph_btn(){
  tft.fillRect(10,80,100,60,MAGENTA);
tft.setCursor(40,100);
tft.setTextSize(3);
tft.setTextColor(GREEN); 
tft.print("PH");
}

void draw_soilmoisture_btn(){

  tft.fillRect(10,180,100,80,MAGENTA);
tft.setCursor(20,190);
tft.setTextSize(2);
tft.setTextColor(GREEN); 
tft.println(" SOIL");
tft.println();
tft.print(" MOISTURE");
}

void draw_back_btn(void){
tft.fillRect(360,10,100,40,YELLOW);
tft.setTextSize(4);
tft.setCursor(362,18);
tft.setTextColor(BLACK);
tft.print("<");
tft.setCursor(385,20);
tft.setTextSize(3);
tft.setTextColor(GREEN); 
tft.print("BACK");
}

void calibrate_btn(){
  tft.fillRect(320,100,150,60,RED);
  tft.setTextSize(2);
  tft.setTextColor(GREEN);
  tft.setCursor(340,110);
  tft.print("Calibrate");
  tft.setCursor(340,140);
  tft.print("Sensors");
}
void draw_manual_btn(){
  tft.fillRect(320,200,150,60,RED);
  tft.setTextSize(2);
  tft.setTextColor(GREEN);
  tft.setCursor(340,210);
  tft.print("Manual");
  tft.setCursor(340,240);
  tft.print("Control");
}
void draw_ok_btn(){
tft.fillRect(360,240,100,40,YELLOW);
tft.setTextSize(4);
tft.setCursor(380,246);
tft.setTextColor(BLACK);
tft.print("OK");
}
void draw_cancel_btn(){
tft.fillRect(170,240,160,40,YELLOW);
tft.setTextSize(4);
tft.setCursor(180,246);
tft.setTextColor(BLACK);
tft.print("CANCEL");
}

void draw_pump_btn(){
  tft.fillRect(10,80,100,60,MAGENTA);
tft.setCursor(20,100);
tft.setTextSize(3);
tft.setTextColor(GREEN); 
tft.print("PUMP");
}

void draw_valve_btn(){
  tft.fillRect(10,180,100,60,MAGENTA);
tft.setCursor(20,200);
tft.setTextSize(3);
tft.setTextColor(GREEN); 
tft.print("VALVE");
}
