void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.print("ghww");

}

void loop() {
  // put your main code here, to run repeatedly:
  char str[10];
  int num=47;
  Serial.println(sprintf(str,"%d",num));
  Serial.println("jfk");
}
