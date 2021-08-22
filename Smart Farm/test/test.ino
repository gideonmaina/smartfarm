#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); 

void setup()

{



Serial.begin(9600);

mySerial.begin(9600);

}

void loop() 

{

if (mySerial.available())

Serial.write(mySerial.read());

if (Serial.available())

{

while(Serial.available())

{

mySerial.write(Serial.read());

}

mySerial.println();

}
}
