int digit1 = 11; //PWM Display pin 1
int digit2 = 10; //PWM Display pin 2
int digit3 = 9; //PWM Display pin 6
int digit4 = 6; //PWM Display pin 8

int segA = A1; //Display pin 14
int segB = 3; //Display pin 16
int segC = 4; //Display pin 13
int segD = 5; //Display pin 3
int segE = A0; //Display pin 5
int segF = 7; //Display pin 11
int segG = 8; //Display pin 15
int num=0;
#define DISPLAY_BRIGHTNESS 500
#define DIGIT_ON HIGH
#define DIGIT_OFF LOW

void dispNumber(byte toDisplay) {

long beginTime = millis();
for(int digit = 4 ; digit > 0 ; digit--) {
//Turn on a digit for a short amount of time
switch(digit) {
case 1:
digitalWrite(digit1, DIGIT_ON);
break;
case 2:
digitalWrite(digit2, DIGIT_ON);
break;
case 3:
digitalWrite(digit3, DIGIT_ON);
break;
case 4:
digitalWrite(digit4, DIGIT_ON);
break;
}
//Turn on the right segments for this digit
ligNumber(toDisplay % 10);
toDisplay /= 10;
delayMicroseconds(DISPLAY_BRIGHTNESS); //Display this digit for a fraction of a second
//Turn off all segments
ligNumber(10);
//Turn off all digits
digitalWrite(digit1, DIGIT_OFF);
digitalWrite(digit2, DIGIT_OFF);
digitalWrite(digit3, DIGIT_OFF);
digitalWrite(digit4, DIGIT_OFF);
}
while( (millis() - beginTime) < 10) ; //Wait for 20ms to pass before we paint the display again
}
void ligNumber(int numToDisplay) {
#define SEGMENT_ON LOW
#define SEGMENT_OFF HIGH
switch (numToDisplay){
case 0:
digitalWrite(segA, SEGMENT_ON);
digitalWrite(segB, SEGMENT_ON);
digitalWrite(segC, SEGMENT_ON);
digitalWrite(segD, SEGMENT_ON);
digitalWrite(segE, SEGMENT_ON);
digitalWrite(segF, SEGMENT_ON);
digitalWrite(segG, SEGMENT_OFF);
break;
case 1:
digitalWrite(segA, SEGMENT_OFF);
digitalWrite(segB, SEGMENT_ON);
digitalWrite(segC, SEGMENT_ON);
digitalWrite(segD, SEGMENT_OFF);
digitalWrite(segE, SEGMENT_OFF);
digitalWrite(segF, SEGMENT_OFF);
digitalWrite(segG, SEGMENT_OFF);
break;
case 2:
digitalWrite(segA, SEGMENT_ON);
digitalWrite(segB, SEGMENT_ON);
digitalWrite(segC, SEGMENT_OFF);
digitalWrite(segD, SEGMENT_ON);
digitalWrite(segE, SEGMENT_ON);
digitalWrite(segF, SEGMENT_OFF);
digitalWrite(segG, SEGMENT_ON);
break;
case 3:
digitalWrite(segA, SEGMENT_ON);
digitalWrite(segB, SEGMENT_ON);
digitalWrite(segC, SEGMENT_ON);
digitalWrite(segD, SEGMENT_ON);
digitalWrite(segE, SEGMENT_OFF);
digitalWrite(segF, SEGMENT_OFF);
digitalWrite(segG, SEGMENT_ON);
break;
case 4:
digitalWrite(segA, SEGMENT_OFF);
digitalWrite(segB, SEGMENT_ON);
digitalWrite(segC, SEGMENT_ON);
digitalWrite(segD, SEGMENT_OFF);
digitalWrite(segE, SEGMENT_OFF);
digitalWrite(segF, SEGMENT_ON);
digitalWrite(segG, SEGMENT_ON);
break;
case 5:
digitalWrite(segA, SEGMENT_ON);
digitalWrite(segB, SEGMENT_OFF);
digitalWrite(segC, SEGMENT_ON);
digitalWrite(segD, SEGMENT_ON);
digitalWrite(segE, SEGMENT_OFF);
digitalWrite(segF, SEGMENT_ON);
digitalWrite(segG, SEGMENT_ON);
break;
case 6:
digitalWrite(segA, SEGMENT_ON);
digitalWrite(segB, SEGMENT_OFF);
digitalWrite(segC, SEGMENT_ON);
digitalWrite(segD, SEGMENT_ON);
digitalWrite(segE, SEGMENT_ON);
digitalWrite(segF, SEGMENT_ON);
digitalWrite(segG, SEGMENT_ON);
break;
case 7:
digitalWrite(segA, SEGMENT_ON);
digitalWrite(segB, SEGMENT_ON);
digitalWrite(segC, SEGMENT_ON);
digitalWrite(segD, SEGMENT_OFF);
digitalWrite(segE, SEGMENT_OFF);
digitalWrite(segF, SEGMENT_OFF);
digitalWrite(segG, SEGMENT_OFF);
break;
case 8:
digitalWrite(segA, SEGMENT_ON);
digitalWrite(segB, SEGMENT_ON);
digitalWrite(segC, SEGMENT_ON);
digitalWrite(segD, SEGMENT_ON);
digitalWrite(segE, SEGMENT_ON);
digitalWrite(segF, SEGMENT_ON);
digitalWrite(segG, SEGMENT_ON);
break;
case 9:
digitalWrite(segA, SEGMENT_ON);
digitalWrite(segB, SEGMENT_ON);
digitalWrite(segC, SEGMENT_ON);
digitalWrite(segD, SEGMENT_ON);
digitalWrite(segE, SEGMENT_OFF);
digitalWrite(segF, SEGMENT_ON);
digitalWrite(segG, SEGMENT_ON);
break;
case 10:
digitalWrite(segA, SEGMENT_OFF);
digitalWrite(segB, SEGMENT_OFF);
digitalWrite(segC, SEGMENT_OFF);
digitalWrite(segD, SEGMENT_OFF);
digitalWrite(segE, SEGMENT_OFF);
digitalWrite(segF, SEGMENT_OFF);
digitalWrite(segG, SEGMENT_OFF);
break;
}
}
void setup()
{
  pinMode(segA, OUTPUT);
pinMode(segB, OUTPUT);
pinMode(segC, OUTPUT);
pinMode(segD, OUTPUT);
pinMode(segE, OUTPUT);
pinMode(segF, OUTPUT);
pinMode(segG, OUTPUT);
pinMode(digit1, OUTPUT);
pinMode(digit2, OUTPUT);
pinMode(digit3, OUTPUT);
pinMode(digit4, OUTPUT);
}
void loop()
{
}
