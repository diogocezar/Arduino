#include <DHTesp.h>
#include <DS1302.h>
#include <ESP8266WiFi.h>
#define DHTPIN D8 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11
#define SAIDARELE1 D2
#define SAIDARELE2 D3
/* Projeto versao 1.0 compilada em 31 de dezembro de 2018 as 22:43
  //ESP Web Server Library to host a web page

  /////////////////////////////////////////////////////////////////////////////////////
  /*ConfiguraÃ§Ãµes necessÃ¡rias, vamos ver como o modulo se comportarÃ¡
*/
IPAddress ip = IPAddress(192, 168, 1, 254);
IPAddress gw = IPAddress(192, 168, 1, 1);
IPAddress sn = IPAddress(255, 255, 255, 0);
const char* ssid = "Zhone_BD30";
const char* password = "znid307322928";
WiFiServer server(5600);

///////////////////////////////////////////////////////////////////////////////////

//const int SAIDARELE1 = D2;//Saida 1 para solenoide de abertura da valvula da agua de alimentaÃ§Ã£o
//const int SAIDARELE2 = D3;//Saida 2 para solenoide de abertura da valvula da agua de alimentaÃ§Ã£o
const int entradaFot = D4; //Entrada fotocelula
const int kCePin   = D5;  // Chip Enable
const int kIoPin   = D6;  // Input/Output
const int kSclkPin = D7;  // Serial Clock
const int entradaUmiTemp = D8;
const int entradaUmidade_berco1 = A0;//Entrada do sendsor de umidade do berÃ§o 1
//int entradaUmidade_berco2 = A1;//Entrada do sendsor de umidade do berÃ§o 1
//int entradaUmidade_berco3 = A2;//Entrada do sendsor de umidade do berÃ§o 1

///////////////////////////////////////////////////////////////////////////////////

int valorUmidade1 = 0;
int valorUmidade2 = 0;
int valorUmidade3 = 0;
bool chora = false;
bool molhou = false;
bool diaNoite = false;
String enviar = "";

///////////////////////////////////////////////////////////////////////////////////
/*Prototipos de funÃ§Ãµes*/

void conectar();
void molhar();
void checarUmidade();
void MostrarTempUmid();
void checarHora();
void printTime();
void dia();
String dayAsString(const Time::Day day);

///////////////////////////////////////////////////////////////////////////////////
// Criando um objeto  DHT11  com pinos acima.

DHTesp dht;

///////////////////////////////////////////////////////////////////////////////////
// Criando um objeto  DS1302  com pinos acima.

DS1302 rtc(kCePin, kIoPin, kSclkPin);

///////////////////////////////////////////////////////////////////////////////////

void setup() {
  //////////////////////////////////////////////////////////////////////////////////
  /*
      GravaÃ§Ã£o de set do relogio */

  //  rtc.writeProtect(false);
  //  rtc.halt(false);
  //    Make a new time object to set the date and time.
  //  Time t(2018, 12, 31, 22, 52, 50, Time::kSunday);
  //   Set the time and date on the chip.
  //rtc.time(t);

  //////////////////////////////////////////////////////////////////////////////////
  Serial.begin(115200);
  delay(10);
  //////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gw, sn);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  /////////////////////////////////////////////////////////
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  server.begin();
  Serial.println("Servidor Iniciado");
  Serial.print(WiFi.localIP());
  pinMode(SAIDARELE1, OUTPUT);
  pinMode(SAIDARELE2, OUTPUT);
  digitalWrite(SAIDARELE1, HIGH);
  digitalWrite(SAIDARELE2, HIGH);
  pinMode(entradaFot, INPUT);
  pinMode(entradaUmidade_berco1 , INPUT);
  dht.setup(DHTPIN, DHTesp::DHT11); // Connect DHT sensor to 4
}

void loop() {
  WiFiClient client = server.available();
  if (!client)
  {
    checarUmidade();
    MostrarTempUmid();
    printTime();
    //molhar();
    checarHora();
    dia();
    //Se nÃ£o houver nenhum cliente podemos retornar pois nÃ£o hÃ¡ nada a fazer
   // return;
  }
  else {
    while (!client.available())
    {
      delay(100);
    }
    String op = client.readString();
 
    Serial.println(op);
    if (op == "Estender")
    {
      digitalWrite(SAIDARELE1, LOW);
      digitalWrite(SAIDARELE2, LOW);
      //fazer algo
      Serial.println("Voce apertou o botao Molhar");
      enviar = "Molhando";
    }
    if (op == "Recolher")
    {
      digitalWrite(SAIDARELE1, HIGH);
      digitalWrite(SAIDARELE2, HIGH);
      //faz algo mÃ¡gico
      Serial.println("Voce apertou o botao Parar");
      enviar = "Parando";
    }

    client.println(enviar);
    //client.stop();
  }


}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void dia()
{
  diaNoite = digitalRead(entradaFot);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void conectar()
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void molhar()
{
  if ((valorUmidade1 >= 2) && (chora == true) && (molhou == false))
  { Serial.println("Molhar");
    do {
      digitalWrite(SAIDARELE1, LOW);
      digitalWrite(SAIDARELE2, LOW);
      checarUmidade();
      delay(200);
    } while (valorUmidade1 < 2);
    molhou = true;
  }
  else if ((valorUmidade1 >= 1) && (chora == true) && (molhou == false))
  { Serial.println("Molhar pouco");
    digitalWrite(SAIDARELE1, LOW);
    digitalWrite(SAIDARELE2, LOW);
    delay(5000);
    molhou = true;
  }
  else
  { Serial.println("NÃ£o molhar");
    digitalWrite(SAIDARELE1, HIGH);
    digitalWrite(SAIDARELE2, HIGH);
    if (chora == false)
    {
      molhou = false;
    }
  }
  Serial.print("Estados dos reles :");
  Serial.print("\t");
  Serial.print("Rele 1 : ");
  Serial.print(SAIDARELE1);
  Serial.print("\t");
  Serial.print("Rele 2 : ");
  Serial.print(SAIDARELE2);

  Serial.println();
  delay(200);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void checarUmidade()
{
  int leitura = analogRead(entradaUmidade_berco1);
  if (leitura <= 1023 && leitura >= 682) {
    valorUmidade1 = 2;
  } else {
    if (leitura <= 681 && leitura >= 341) {
      valorUmidade1 = 1;
    }
    else {
      if (leitura <= 340 && leitura >= 0) {
        valorUmidade1 = 0;
      }
    }
  }
  delay(100);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MostrarTempUmid()
{
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  delay(dht.getMinimumSamplingPeriod());
  float h = dht.getHumidity();
  float t = dht.getTemperature();
  // testa se retorno Ã© valido, caso contrÃ¡rio algo estÃ¡ errado.
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();

    Serial.println(dht.getStatusString());
    Serial.print("\t");
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.print(temperature, 1);
    Serial.print("\t\t");
    Serial.println();
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
  Serial.print("Pronto para molhar  :  ");
  Serial.print(chora);
  Serial.println();
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

