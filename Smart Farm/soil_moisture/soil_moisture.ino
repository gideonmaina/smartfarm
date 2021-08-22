/* 
  Soil Moisture Sensor  
  modified on 21 Feb 2019 
  by Saeed Hosseini @ Electropeak 
  https://electropeak.com/learn/ 
*/
#define SensorPin A0 
 float sensorValue = 0; 
 int minADC = 642;                       // replace with min ADC value read in air
int maxADC = 375;                     // replace with max ADC value read fully submerged in water
bool is1V1Output = false;             // set true if 1.1V output sensor is used for 3V set to false
int mappedValue,moistureValue;
//#define INTERNAL 1.1
void setup() { 
  Serial.begin(9600); 
  if(is1V1Output == true)
  analogReference(INTERNAL1V1); //set ADC reference to internal 1.1V
}

void loop() { 
//  for (int i = 0; i <= 100; i++) 
//  { 
//    sensorValue = sensorValue + analogRead(SensorPin); 
//    delay(1); 
//  } 
//  sensorValue = sensorValue/100.0; 
//  Serial.println(sensorValue); 
//  delay(30); 

// read the moisture value:
moistureValue = analogRead(SensorPin);


// print ADC results to the serial monitor:
Serial.print("ADC = " );
Serial.print(moistureValue);
Serial.print(", " );

mappedValue = map(moistureValue,minADC,maxADC, 0, 100); 

// print mapped results to the serial monitor:
Serial.print("Moisture value = " );
Serial.println(mappedValue);
 
// wait 500 milliseconds before the next loop
delay(500);

}
