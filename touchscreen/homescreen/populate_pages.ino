void gotoPage(int page_id){
  switch (page_id){
    case 1:
          populate_homescreen_page();
          break;
    case 2: populate_calibration_page();
           break;
     default:
            page_id=HOMESCREEN_PAGE;
            break;    
  }
}

void populate_homescreen_page(){
currentPage=HOMESCREEN_PAGE;
//tft.fillScreen(BLACK);
//tft.drawRect(0,0,300,320,MAGENTA);
tft.fillRect(0,0,480,320,MAGENTA);
tft.drawRect(300,0,180,320,BLACK);
tft.fillRect(300,0,180,320,BLACK); 
calibrate_btn();
draw_manual_btn();
tft.setTextSize(3);
tft.setTextColor(YELLOW); 
tft.setCursor(40,10);
tft.println("SENSOR VALUES");
tft.print("_______________");

tft.setTextSize(2);
tft.setTextColor(GREEN); 
tft.setCursor(10,70);
tft.print("TEMP: ");
tft.setCursor(10,100);
tft.print("HUM: ");
tft.setCursor(10,130);
tft.print("PH: ");
tft.setCursor(10,160);
tft.print("MOIS: ");
}

void populate_calibration_page(){
currentPage=CALIBRATION_PAGE; 
previousPage=HOMESCREEN_PAGE;
tft.fillScreen(BLACK);
tft.setTextSize(2);
tft.setTextColor(YELLOW); 
tft.setCursor(10,10);
tft.println("CALIBRATION SETTINGS");
tft.print("__________________________");

draw_ph_btn();
draw_soilmoisture_btn();
draw_back_btn();
tft.drawRect(150,80,320,230,YELLOW);

}

void startPage(){

tft.setCursor(180,100);
tft.setTextSize(4);
tft.setTextColor(GREEN);
tft.print("SMART");
tft.setCursor(190,150);
tft.println("FARM");
delay(2000);

populate_homescreen_page();

}


void populate_manual_control_page(){
  currentPage=MANUAL_CONTROL_PAGE;
  previousPage=HOMESCREEN_PAGE;
  
  Serial.println("Now in manual control page");
 
tft.fillScreen(BLACK);
tft.setTextSize(2);
tft.setTextColor(YELLOW); 
tft.setCursor(10,10);
tft.println("MANUAL CONTROL");
tft.print("__________________________");

draw_back_btn();
draw_pump_btn();
draw_valve_btn();
}



void soil_moisture_settings(){
  tft.setCursor(160,90);
  tft.setTextSize(2);
  tft.setTextColor(YELLOW);
  tft.print("Place soil moisture sensor ");
  tft.setCursor(160,120);
  tft.print("in air and press OK");
   
  draw_ok_btn();
  draw_cancel_btn();
 
  while(wait){
     tp=ts.getPoint();
     if(tp.z>MINPRESSURE && tp.z<MAXPRESSURE){  
    if (SwapXY != (Orientation & 1)) SWAP(tp.x, tp.y);
    x_coord=map(tp.x,TS_RT,TS_LEFT,0,tft.width());
    y_coord=map(tp.y,TS_BOT,TS_TOP,0,tft.height());
   
    if(ok_btn_touch(x_coord,y_coord)){
    
      
     tft.setCursor(160,190);
     tft.setTextSize(2);
     tft.setTextColor(CYAN);
     tft.print("touched");
     Serial.print("OK BTN: ");
     Serial.print(x_coord);
     Serial.print(y_coord);
  
    }

    else if(cancel_btn_touch(x_coord,y_coord)){
      wait=false;
      tft.fillRect(150,80,320,230,BLACK);
    }
    
   }
  }
  wait=true;
   
}
