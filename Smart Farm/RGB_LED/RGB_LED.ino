
#define blue 13
#define green 12
#define red 11

void setup() {
  // put your setup code here, to run once:
  pinMode(blue,OUTPUT);
  // pinMode(green,OUTPUT);
   // pinMode(red,OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:

for(int i=0;i<=255;i++){
  analogWrite(green,i);
  
  analogWrite(blue,i);
  analogWrite(red,i);
  delay(1000);
}


}
