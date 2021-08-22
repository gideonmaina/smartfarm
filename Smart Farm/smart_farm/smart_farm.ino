
#include <Nokia_LCD.h>
#include <DHT.h>;
//Constants
#define green_led 6
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define MoistureSensorPin A0 
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
int minADC = 642;     // replace with min ADC value read in air
int maxADC = 375;     // replace with max ADC value read fully submerged in water
bool is1V1Output = false;      // set true if 1.1V output sensor is used for 3V set to false
int mappedValue,moistureValue;


Nokia_LCD lcd(13 /* CLK */, 12 /* DIN */, 11 /* DC */, 10 /* CE */, 9 /* RST */);
void setup() {
   Serial.begin(9600);
   if(is1V1Output == true)
  analogReference(INTERNAL1V1); //set ADC reference to internal 1.1V
  pinMode(green_led, OUTPUT);
  dht.begin();
  // put your setup code here, to run once:
 // Initialize the screen
  lcd.begin();
  // Set the contrast
  lcd.setContrast(60);  // Good values are usualy between 40 and 60
  // Clear the screen by filling it with black pixels

  lcd.clear(true);
  lcd.setCursor(1,1);
  lcd.print("Smart Farm");
  
 delay(1000);
 lcd.clear();
   calibration();
   lcd.clear();
    lcd.print("TEMP:");
    lcd.setCursor(0,1);
    lcd.print("HUM:");
    lcd.setCursor(0,2);
    lcd.print("MOISTURE:");
    
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    // read the moisture value:
    moistureValue = analogRead(MoistureSensorPin);
    mappedValue = map(moistureValue,minADC,maxADC, 0, 100);
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.print(" Celsius");
    Serial.print(", Moisture: ");
    Serial.print(mappedValue);
    Serial.println();
  
    lcd.setCursor(28,0);
    lcd.print(temp);
    lcd.print(" C");
    lcd.setCursor(28,1);
    lcd.print(hum);
    lcd.print(" %");
    lcd.setCursor(44,2);
    lcd.print(mappedValue);
    if(hum>80) digitalWrite(green_led, HIGH);
    else digitalWrite(green_led,LOW);
    
    //delay(1000); //Delay 2 sec.

}

void calibration(){
  int sampleSize=60;
  lcd.clear();
  lcd.print("CALIBRATING....");
  delay(1000);
  lcd.clear();
  lcd.print("Place Soil Moisture Sensor in air and press ENTER KEY");
  while(!Serial.available()){
    while(Serial.read()!='y'){};
       for(int i=0;i<=sampleSize;i++){
       minADC+=analogRead(MoistureSensorPin);
       Serial.print("min ADC:  ");
       Serial.print(minADC);
       Serial.println();
       }
      minADC=minADC/sampleSize;
      Serial.print("Average minADC:  ");
      Serial.print(minADC);
      lcd.clear();
      lcd.print("minADC: ");
      lcd.print(minADC);
      
      
   
 delay(1000);
 lcd.clear(true);
 lcd.print("Now Submerge Soil Moisture Sensor in Water and Press ENTER KEY");
 
//while(!Serial.available()){
while(Serial.read()!='y'){};
for(int i=0;i<=sampleSize;i++){
     maxADC+=analogRead(MoistureSensorPin);
       Serial.print("max ADC:  ");
       Serial.print(maxADC);
       Serial.println();
       }
      maxADC=maxADC/sampleSize;
      lcd.clear();
      lcd.print("maxADC: ");
  
      lcd.print(maxADC);
      
      break;
}



  }
  
  


    
  
  
  
