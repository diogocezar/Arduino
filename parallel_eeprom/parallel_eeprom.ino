byte outPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}; // 16 pins for address output
byte inPins[] = { 24, 26, 28, 30, 32, 34, 36, 38}; // 8 pins for data lines


// These two set the reading range. It may also be like 0x1C000 to 0x1FFFF
int minadr = 0;
int maxadr = 1000;

void addressOut(int address) {
  int mask = 1;
  for (int i = 0; i < 16; i++) { // i < number of outpins
    if ((mask & address) != 0) digitalWrite(outPins[i], HIGH);
    else digitalWrite(outPins[i], LOW);
    mask = mask << 1;
    
  }
  
  
}

int readIn() {
  int input = 0;
  int mask = 1;
  for (int i = 0; i < 8; i++) { // i < number of inpins
    if (digitalRead(inPins[i]) == HIGH){input |= mask;}
    mask = mask << 1;
    
     //Serial.print(mask);
  }
 return(input);
  
}

void setup() {
  // PIN MODES
 

  for (int i = 0; i < 16; i++) { // i < number of outpins
    pinMode(outPins[i], OUTPUT);
  }
  for (int i = 0; i < 8; i++) { // i < number of outpins
    pinMode(inPins[i], INPUT);
  }

  // Initialize READ state
 

  Serial.begin(9600);
}

void loop() {
  char aux;
 // delay(2000);
  for (int i = minadr; i < maxadr; i++) {
    
    addressOut(i);
    if(i%32==0) Serial.print('\n');
  // Serial.print(i);
  //  Serial.print('=');
//  aux=char(readIn());
    Serial.write(readIn());
    
    Serial.print(' ');
   // Serial.print(readIn()); // You may have to change how the output it's interpreted: BYTE, HEX, BIN
    delay(15);
  }
}
