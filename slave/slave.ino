#include <Wire.h>

void setup() {
  // inicializando as tres portas seriais
  Wire.begin(2);
  Serial.begin(9600);
  UCSR0C = UCSR0C | B00100000;//Even par
  UCSR0C = UCSR0C | B00000000;//2stopbits   
}

  char byt[30],nadaaver[30];
  int pes[30],peso[10];
  long soma;
  int i=0;
  
void loop() {
  
  soma=0;
  long multi = 100000;
  
  if (Serial.available()) {
    for(i=0;i<5;i++){

      Serial.readBytes(byt,30);     
    }
  }

  for(i=0;i<30;i++)Serial.print(byt[i]);
  
  Serial.println();
  
  for(i=5;i<11;i++){    
    Serial.print(byt[i]);
   
    soma += (byt[i]-48)* multi;
    
    multi/=10;    
  }
  
long byt2= Wire.read();
    
  if(byt[13]-48==1){
      
    Serial.print("Peso : ");
    Serial.println(soma);
    
  }else{
    Serial.println("Peso instavel");
    
  }
  Wire.write(soma+byt2);
  Wire.endTransmission();
  
}
