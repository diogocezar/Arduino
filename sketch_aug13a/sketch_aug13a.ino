/*
  Arduino + 74HC595 + 74HC4511 7-Segment Control
  2012 Ricardo Sequeira
  www.ricardo-sequeira.com
*/



//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 9;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
//Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;


// Binary digits representation
int seven_seg_digits[10][4] = { { 0,0,0,0 },  // = 0
                                 { 0,0,0,1 },  // = 1
                                 { 0,0,1,0 },  // = 2
                                 { 0,0,1,1 },  // = 3
                                 { 0,1,0,0 },  // = 4
                                 { 0,1,0,1 },  // = 5
                                 { 0,1,1,0 },  // = 6
                                 { 0,1,1,1 },  // = 7
                                 { 1,0,0,0 },  // = 8
                                 { 1,0,0,1 }   // = 9
                                 };
                                 


void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() {
  

 

  for(int j=0; j<200; j++){
    disp7SegmWrite(j);
    delay(100);
  }
}

// Function that performs writing of numbers in the 7-Segment Display
void disp7SegmWrite(int number) {
  int num1=0, num2=0;
  
  if((number < 0) || (number > 99)){
    number = 0;
  }
  
  num1=number/10;
  num2=number%10;
  
  // the bits you want to send
  byte bitsToSend = 0;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

  //Write num2 (MSD - most significant digit)
  bitWrite(bitsToSend, 0, seven_seg_digits[num1][3]);
  bitWrite(bitsToSend, 1, seven_seg_digits[num1][2]);
  bitWrite(bitsToSend, 2, seven_seg_digits[num1][1]);
  bitWrite(bitsToSend, 3, seven_seg_digits[num1][0]);

  //Write num2 (LSD - less significant digit)  
  bitWrite(bitsToSend, 4, seven_seg_digits[num2][3]);
  bitWrite(bitsToSend, 5, seven_seg_digits[num2][2]);
  bitWrite(bitsToSend, 6, seven_seg_digits[num2][1]);
  bitWrite(bitsToSend, 7, seven_seg_digits[num2][0]);
  // shift the bits out
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

  // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);
}


