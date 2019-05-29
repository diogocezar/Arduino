#include <LiquidCrystal.h>

LiquidCrystal lcd( 12, 11, 5 , 4 , 3 , 2 ) ;

int sensoragua;
int boia1;
int boia2;
int bomba1;
int bomba2;
int gatilho = 13;
int echo = A0;
float tempo; // para armazenar o tempo de ida e volta do sinal em microsegundos
float cm; // para armazenar a distância em centímetros
bool flag = false;


void ultrasson() {
  digitalWrite(gatilho, HIGH);
  delayMicroseconds(10);
  digitalWrite(gatilho, LOW);

  // medir tempo de ida e volta do pulso ultrassônico
  tempo = pulseIn(echo, HIGH);

  // calcular as distâncias em centímetros e polegadas
  cm = abs((tempo / 29.4 / 2) - 21);
  lcd.setCursor(1, 4);
  lcd.print("AGUA :");
  lcd.print(cm, 1.2f);

}
void setup() {
  lcd. begin (20, 4);

  pinMode(6, INPUT);//sensoragua
  pinMode(7, INPUT);//boia1
  pinMode(8, INPUT);//boia2
  pinMode(9, OUTPUT);//bomba1
  pinMode(10, OUTPUT);//bomba2
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  pinMode(gatilho, OUTPUT); // deixa pino em LOW
  digitalWrite(gatilho, LOW);
  delayMicroseconds(10);
  pinMode(echo, INPUT); // configura pino ECHO como entrada


}

void loop() {

  sensoragua = digitalRead(6); //se houver agua, comeca o codigo
  lcd.clear();
  if (sensoragua == 1) {

    lcd.setCursor(1, 0);
    lcd.print("PRESENCA DE AGUA");
    //delay(500);
    boia1 = digitalRead(7); //se boia1 acionada, liga bomba1

    if (boia1 == 0) {
      digitalWrite(9, LOW); //liga bomba 1
      lcd.setCursor(1, 1);
      lcd.print("BOMBA 1 LIGADA");
      if (flag == true){
        lcd.setCursor(1, 2);
      lcd.print("BOMBA 2 LIGADA");
      }
      boia2 = digitalRead(8);
      if (boia2 == 0) { //se boia 2 acionada, liga bomba 2
        digitalWrite(10, LOW); //liga bomba 2
        lcd.setCursor(1, 2);
        lcd.print("BOMBA 2 LIGADA");
        flag = true;
      }

    }
    else {    //quando a boia 1 nao estiver acionada desliga as duas bombas

      flag = false;
      lcd.setCursor(1, 2);
      lcd.print("BOMBAS DESLIGADAS");
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
    }

    ultrasson();  //imprime nivel de agua no lcd
    // delay(300);
  }
  else
  {

    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    lcd.setCursor(1, 2);
    lcd.print("SEM AGUA");

  }
  delay(1000);
}

