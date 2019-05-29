

#include <Hx711.h>
Hx711 scale(A2, A3);
uint8_t KeyZero = 6;
uint8_t KeySpam = 7;
long zero=0;
long tara=0;
float spam=1;
float aux=1;
 bool flag=false;
   
void setup() 
{  
  
   Serial.begin(9600);


  pinMode(KeyZero, INPUT_PULLUP);           // set pin to input
  pinMode(KeySpam, INPUT_PULLUP);           // set pin to input

}  
  
void loop() 
{  

long a = scale.getValue()/100;
Serial.println(a);
if ( (digitalRead(KeyZero)==LOW)& (flag==false)){
zero=a;
flag=true;}
else if((digitalRead(KeyZero)==LOW)& (flag==true)){
  zero=a;

}
tara=a-zero;
if( digitalRead(KeySpam)==LOW){
spam=200/(float(a-zero));

 
}
 Serial.println(spam,5.6f); 
aux=tara*spam;

char data[9];
char *valor = dtostrf(aux,8,0,data);
  Serial.println(valor);  // picture loop   
 
}     
