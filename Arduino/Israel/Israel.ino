#include <dht.h>

//Include LCD library
#include <LiquidCrystal.h>
#define DHTPIN A0 // pino que estamos conectado
#include <dht.h>

#define dht_dpin A0

dht DHT;
const int LM35 = A1; // Define o pino que lera a saída do LM35
float temperatura; // Variável que armazenará a temperatura medida
 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
  Serial.begin(9600);
  
  lcd.begin(20, 4);

  lcd.setCursor(4, 0);
  lcd.print("Bem vindo");

}

void loop() {
  DHT.read11(dht_dpin);
  int h = DHT.humidity;
  int t = DHT.temperature;
  temperatura = (float(analogRead(LM35)) * 5 / (1023)) / 0.01;

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  //Print a message to second line of LCD1
  
    lcd.print("Umidade: ");
    lcd.print(h);
    lcd.print(" t");
    lcd.setCursor(0,2);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print(" C ");
  lcd.setCursor(0, 3);
  lcd.print("Temp LM35: ");
  lcd.print(temperatura);
  lcd.print(" C ");
 
  delay(1000);
}
