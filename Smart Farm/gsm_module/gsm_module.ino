 #include <SoftwareSerial.h>
#define blue 22
#define green 24
#define red 26
SoftwareSerial mySerial(19,18); // RX, TX of the Arduino Mega  (NOTE!!! connected to TX and RX of GSM module respectively)


const String PUMPON;
const String PUMPOFF;
bool pump=false;
int pumpLed=7;
bool inbuiltLed=true;
void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(red,OUTPUT);
  delay(100);
  
  
}


void loop()
{
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'r':
      RecieveMessage();
      break;
  }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());

if (mySerial.available())              // if date is comming from softwareserial port ==> data is comming from gprs shield
  Serial.write(mySerial.read());
  if (Serial.available())                // if data is available on hardwareserial port ==> data is comming from PC or notebook 
  mySerial.write(Serial.read()); 
}


 void SendMessage()
{
  Serial.println(mySerial.println("AT+BTSTATUS?"));
  Serial.println(mySerial.println("AT+IPR?"));
 Serial.println(mySerial.println("AT+COPS=?"));
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+254715123973\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z 
   digitalWrite(blue,HIGH);
      digitalWrite(green,LOW);
  delay(1000);
}


 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  digitalWrite(LED_BUILTIN,inbuiltLed);
  digitalWrite(blue,LOW);
  digitalWrite(green,HIGH);
  delay(1000);
 }
 
