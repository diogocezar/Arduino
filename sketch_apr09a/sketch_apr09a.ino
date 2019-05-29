byte outPins[] = {2,3,4,5,6,7, 8,9,10,11,12,13,14,15,16,17}; // 16 pins for address output
byte inPins[] = {24,26,28,30,32,34,36,38}; // 8 pins for data lines

// Control state pins: OutputEnable, WriteEnable, ChipEnable
int oe = 23;
int we = 22;
int ce = 21;

// These two set the reading range. It may also be like 0x1C000 to 0x1FFFF
int minadr = 0;
long maxadr = 65000;

void addressOut(long address){
byte mask = 1;
for(int i = 0; i<16; i++) { // i < number of outpins
    if((mask & address) != 0) {
    digitalWrite(outPins[i], HIGH);
    } 
    else
   { digitalWrite(outPins[i],LOW);
    mask = mask << 1;
   }
}
}

byte readIn(){
byte input = 0;
byte mask = 1;
for(int i = 0; i<8; i++){ // i < number of inpins
    if(digitalRead(inPins[i]) == HIGH) input |= mask;
    mask = mask << 1;
}
  return(input);
} 

void setup() {
// PIN MODES
pinMode(oe, OUTPUT);
pinMode(we, OUTPUT);
pinMode(ce, OUTPUT);

for(int i = 0; i<16; i++){  // i < number of outpins
    pinMode(outPins[i], OUTPUT);
}
for(int i = 0; i<8; i++){  // i < number of outpins
    pinMode(inPins[i], INPUT);
}
  
// Initialize READ state
digitalWrite(oe, LOW);
digitalWrite(ce, LOW);
digitalWrite(we, HIGH);
  
Serial.begin(9600);
}

void loop() {
  for(long i = minadr; i < maxadr; i++) {
  addressOut(i);
  delay(10);
  Serial.print(i);
  Serial.print(readIn(), HEX); 
   Serial.println();// You may have to change how the output it's interpreted: BYTE, HEX, BIN
  }
}
