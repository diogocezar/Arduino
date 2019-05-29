int led =2;
int led1=3;

void setup() {
  // put your setup code here, to run once:
pinMode(led,OUTPUT);
pinMode(led1,OUTPUT);
}

void loop() {
  digitalWrite(led,HIGH);
  digitalWrite(led1,HIGH);
  delay(1000);
  digitalWrite(led,LOW);
  digitalWrite(led1,LOW);

}
