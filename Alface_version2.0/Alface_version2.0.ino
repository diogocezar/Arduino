#include <stdio.h>
#include <DS1302.h>
int saida_pos = 8;
int saida_neg = 9;
int sensor_umidade = A0;
/////////////////////////////
int valor_umi = 0;
bool chora = false;
bool molhou = false;
void checarUmidade();
void checarHora();
void printTime();
String dayAsString(const Time::Day day);
const int kCePin   = 5;  // Chip Enable
const int kIoPin   = 6;  // Input/Output
const int kSclkPin = 7;  // Serial Clock

// Create a DS1302 object.
DS1302 rtc(kCePin, kIoPin, kSclkPin);


void setup() {
  //  rtc.writeProtect(false);
  // rtc.halt(false);
  // Make a new time object to set the date and time.
  // Time t(2018, 5, 19, 07, 52, 50, Time::kSunday);
  // Set the time and date on the chip.
  // rtc.time(t);
  Serial.begin(9600);
  /////////////////////////////////////////////////////
  pinMode(saida_pos, OUTPUT);
  pinMode(saida_neg, OUTPUT);
  pinMode(sensor_umidade, INPUT);
  digitalWrite(saida_pos, LOW);
  digitalWrite(saida_neg, LOW);

}

void loop() {
  checarUmidade();
  checarHora();
  printTime();
  if ((valor_umi >= 2) && (chora == true) && (molhou == false))
  { Serial.println("Molhar");
    do {
      digitalWrite(saida_pos, HIGH);
      digitalWrite(saida_neg, HIGH);
      checarUmidade();
      delay(200);
    } while (valor_umi < 2);
    molhou = true;
  }
  else if ((valor_umi >= 1) && (chora == true) && (molhou == false))
  { Serial.println("Molhar pouco");
    digitalWrite(saida_pos, HIGH);
    digitalWrite(saida_neg, HIGH);
    delay(5000);
    molhou = true;
  }
  else
  { Serial.println("Não molhar");
    digitalWrite(saida_pos, LOW);
    digitalWrite(saida_neg, LOW);
    if (chora == false)
    {
      molhou = false;
    }
  }
  delay(200);
}
void checarUmidade()
{
  int leitura = analogRead(sensor_umidade);
  Serial.println(leitura);
  if (leitura <= 1023 && leitura >= 682) {
    valor_umi = 2;
  } else {
    if (leitura <= 681 && leitura >= 341) {
      valor_umi = 1;
    }
    else {
      if (leitura <= 340 && leitura >= 0) {
        valor_umi = 0;
      }
    }
  }
  delay(100);
}
void checarHora()
{

  Time hora = rtc.time();
  if ((hora.hr == 7) && (hora.min <= 30))
  {
    chora = true;
  }

  else if ((hora.hr == 18) && (hora.min <= 30))
  {
    chora = true;
  }
  else
  {
    chora = false;
  }
  Serial.println(chora);
  delay(100);
}
String dayAsString(const Time::Day day) {
  switch (day) {
    case Time::kSunday: return "Sunday";
    case Time::kMonday: return "Monday";
    case Time::kTuesday: return "Tuesday";
    case Time::kWednesday: return "Wednesday";
    case Time::kThursday: return "Thursday";
    case Time::kFriday: return "Friday";
    case Time::kSaturday: return "Saturday";
  }
  return "(unknown day)";
}
void printTime() {
  // Get the current time and date from the chip.
  Time t = rtc.time();
  // Name the day of the week.
  const String day = dayAsString(t.day);
  // Format the time and date and insert into the temporary buffer.
  char buf[50];
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day.c_str(),
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);
  Serial.println(buf);
}
