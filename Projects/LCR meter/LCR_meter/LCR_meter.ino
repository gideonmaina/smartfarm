/** Program to displace impedance and lcr values on a LCD from an AD5933 using an Arduino board  */

#include "Wire.h"
#include "math.h"
#include "AD5933.h"


/* setting up LCD */
#include "LiquidCrystal.h"
LiquidCrystal lcd(8,9,4,5,6,7);

/* defining constants */
#define PI 3.14159265358979323846
#define BASE_FREQ  (100000) //starting frequency  /** Set starting frequency **/
#define INCR_FREQ_INTERVALS  (1000)  //frequency increment
#define STEPS    (40)    // 
#define R_REF  (10000) //reference resistor

char str[10];
int phase[STEPS+1];
double gain[STEPS+1];



void setup() { 
   Wire.begin();
   lcd.begin(16,4);
  lcd.setCursor(0,0);
  lcd.print("LCR METER");
  lcd.setCursor(0,2);
  lcd.print("INITIATING TEST");
  delay(2000);

  /******  CONFIGURATION  AD5933 MODULE INITIALIZATION  ***/ 
  
  if (!(AD5933::reset() && 
        AD5933::setStartFrequency(BASE_FREQ) &&
        AD5933::setInternalClock(true) &&
        AD5933::setPGAGain(PGA_GAIN_X1) &&
        AD5933::setNumberIncrements(STEPS)&&
        AD5933::setIncrementFrequency(INCR_FREQ_INTERVALS) 
         ))
        {   
            lcd.clear();
            lcd.print("Initialization failed!");
            while (true) ;
        }

  /********  PERFORMING CALIBRATION SWEEP *****/
  if (AD5933::calibrate(gain, phase, R_REF, STEPS+1)){
    lcd.clear();  
    lcd.print("Calibration Successful!");
    
    }
    
  else{
      lcd.clear();
      lcd.print("Calibration failed!");
  }
    
}



void loop() {
    
  freqSweep();
  // Delay
  delay(5000);
}



void freqSweep() {
    /*** Data held in arrays */
    int real[STEPS+1];
    int imag[STEPS+1];

    /*** START FREQUENCY SWEEP */
    if (AD5933::frequencySweep(real, imag, STEPS+1)) {
      
    /** Show freq data */
      int calc_freq = BASE_FREQ/1000;
      for (int j = 0; j < STEPS+1; j++, calc_freq += INCR_FREQ_INTERVALS/1000) {
        
        /**Display raw frequency data  */ 
        lcd.clear();
        lcd.print(sprintf(str,"Freq: %d",calc_freq));

        //display impedance in rectangular form
        lcd.setCursor(0,1);
        lcd.print(sprintf(str,"R= %.2f",real[j]));
        lcd.print(sprintf(str," I= %.2f",imag[j]));
        
        /*** displaying impedance in polar form */

        /*** Calculate impedance   */
        double magnitude = sqrt(pow(real[j], 2) + pow(imag[j], 2));
        double impedance = 1/(magnitude*gain[j]);
        lcd.setCursor(0,2);
        lcd.print(sprintf(str,"|Z|= %2.f ",impedance)); //display impedance;
          
         /***Compute Phase difference ***/
         double ph= atan(imag[j]/real[j]);
         lcd.setCursor(8,2);
         lcd.print(sprintf(str, "ph=%.2f",ph));
       
        /***     Compute inductance      ***/
         double L=imag[j]/(2*PI*calc_freq); // inductance = reactance/(2*PI*frequency)
         lcd.setCursor(0,3);

          //display inductance in Henries
          if( L<1.0 )   lcd.print(sprintf( str, "L%4.1fmH ", L * 1000.0 ));
          else if(L<10.0 )  lcd.print(sprintf( str, "L%2.3fH  ", L ));
          else if(L<100.0) lcd.print(sprintf( str, "L%3.2f  ", L ));
          else lcd.print("L=---");


        /**** Compute Capacitance ****/

        double C = -1000000.0 / ( imag[j] * 2.0 * PI * calc_freq );    // uF  //Capacitance= -1/(reactance*2*PI*Frequency)
         
         lcd.setCursor(8,3); //set cursor on same line as inductance values
         
         //display capacitance in Farads
         if( C<1.0)        lcd.print(sprintf( str, "C%4.1fnF ", C * 1000.0 ));
         else if( C<10.0)  lcd.print(sprintf( str, "C%2.3fuF ", C ));
         else if( C<100.0 ) lcd.print(sprintf( str, "C%3.2fuF ", C ));
         else lcd.print(" C=---");


       
       }
      
    } else {
      lcd.clear();
      lcd.print("Frequency sweep failed!");
    }
}
