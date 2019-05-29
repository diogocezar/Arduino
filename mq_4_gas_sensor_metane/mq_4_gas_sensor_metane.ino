const int mq4=A0;
void setup() {
  Serial.begin(9600);

}

void loop() {
  
  Serial.println(analogRead(mq4));
  delay(200);

}
