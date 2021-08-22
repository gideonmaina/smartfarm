void check_btn_pressed(int currentPage){
  if(calibrate_btn_touch(x_coord, y_coord,currentPage)){
   gotoPage(CALIBRATION_PAGE);
    
    }

   else if(manual_btn_touch(x_coord,y_coord,currentPage)){
   populate_manual_control_page();
   Serial.println("manual control page");
   }
   
   else if(back_btn_touch(x_coord,y_coord)){
    
    
    gotoPage(previousPage);
    
   }
  else if(sm_btn_touch(x_coord,y_coord,currentPage)){
    soil_moisture_settings();
  }

 


   
}


bool calibrate_btn_touch(int x,int y,int currentPage){
  if(x>=330&&x<=480&&y>=100&&y<=170&& currentPage==HOMESCREEN_PAGE){
    return true;
  }
  else{
    return false;
  }
}
bool manual_btn_touch(int x,int y,int currentPage){
  if(x>=330&&x<=480&&y>=200&&y<=270&& currentPage==HOMESCREEN_PAGE){
    Serial.println("manual button touched");
    return true;
  }
  else{
    return false;
  }
}
bool back_btn_touch(int x,int y){
 if(x>=360&&x<=460&&y>=10&&y<=50&&currentPage !=HOMESCREEN_PAGE){
  return true;  
 }
 else{
  return false;
 }
}

bool sm_btn_touch(int x,int y, int currentPage){
   if(x>=10&&x<=110&&y>=180&&y<=260&&currentPage==CALIBRATION_PAGE){
    Serial.println("SM BUTTON PRESSED");
  return true;  
 }
 else{
  
  Serial.println("ERROR: Check SM button Settings");
  Serial.print("CURRENT PAGE: ");
  Serial.print(currentPage);
  return false;
 }
}

bool ok_btn_touch(int x, int y){
  if(x>=360&&x<=460&&y>=240&&y<=280){
  return true;  
 }
 else{
  return false;
 }
}
bool cancel_btn_touch(int x, int y){
  if(x>=170&&x<=330&&y>=240&&y<=280){
  return true;  
 }
 else{
  return false;
 }
}
