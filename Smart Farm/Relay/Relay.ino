
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()>0){
  switch(Serial.read()){
    case 'o':
    
    digitalWrite(4,HIGH);
    Serial.println("BULB ON");
    break;

    case 'c':
    digitalWrite(4,LOW);
      Serial.println("BULB OFF");
    break;
    
    
    }
  
  
  }
}
