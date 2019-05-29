#include <DS1302.h>
#include <ESP8266WiFi.h>
/* Projeto versao 1.0 compilada em 27 de dezembro de 2018 as 22:43
  //ESP Web Server Library to host a web page

/////////////////////////////////////////////////////////////////////////////////////
  /*Configurações necessárias, vamos ver como o modulo se comportará
*/
IPAddress ip = IPAddress(192, 168, 1, 254);
IPAddress gw = IPAddress(192, 168, 1, 1);
IPAddress sn = IPAddress(255, 255, 255, 0);
const char* ssid = "Zhone_BD30";
const char* password = "znid307322928";
WiFiServer server(5600);

///////////////////////////////////////////////////////////////////////////////////

const int saidaRele1 = D2;//Saida 1 para solenoide de abertura da valvula da agua de alimentação
const int saidaRele2 = D3;//Saida 2 para solenoide de abertura da valvula da agua de alimentação
const int entradaFotocelula=D4;//Entrada fotocelula
//const int entradaUmidadeTemperatura=D5;
const int kCePin   = D5;  // Chip Enable
const int kIoPin   = D6;  // Input/Output
const int kSclkPin = D7;  // Serial Clock
int entradaUmidade_berco1 = A0;//Entrada do sendsor de umidade do berço 1
int entradaUmidade_berco2 = A1;//Entrada do sendsor de umidade do berço 1
int entradaUmidade_berco3 = A2;//Entrada do sendsor de umidade do berço 1

///////////////////////////////////////////////////////////////////////////////////

int valor_umi = 0;
bool chora = false;
bool molhou = false;
String enviar = "";

///////////////////////////////////////////////////////////////////////////////////
/*Prototipos de funções*/

  void conectar();
  void molhar();
  void checarUmidade();
  void checarHora();
  void printTime();
  String dayAsString(const Time::Day day);

///////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////
// Criando um objeto  DS1302  com pinos acima.

DS1302 rtc(kCePin, kIoPin, kSclkPin);

///////////////////////////////////////////////////////////////////////////////////

void setup() {
  //////////////////////////////////////////////////////////////////////////////////
  /*
      Gravação de set do relogio

    //  rtc.writeProtect(false);
    // rtc.halt(false);
    // Make a new time object to set the date and time.
    // Time t(2018, 5, 19, 07, 52, 50, Time::kSunday);
    // Set the time and date on the chip.
    // rtc.time(t);
  */
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
  pinMode(saida_pos, OUTPUT);
  pinMode(saida_neg, OUTPUT);
  pinMode(sensor_umidade, INPUT);
  digitalWrite(saida_pos, LOW);
  digitalWrite(saida_neg, LOW);

}

void loop() {
 /* WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  String op = client.readStringUntil('\r');
  Serial.println(op);
  client.flush();
  if (op.indexOf("/Estender") != -1)
  {
    digitalWrite(saida_pos, HIGH);
    digitalWrite(saida_neg, HIGH);
    //fazer algo
    Serial.println("Voce apertou o botao Molhar");
    enviar = "Molhando";
  }
  else if (op.indexOf("/Recolher") != -1)
  {
    digitalWrite(saida_pos, LOW);
    digitalWrite(saida_neg, LOW);
    //faz algo mágico
    Serial.println("Voce apertou o botao Parar");
    enviar = "Parando";
  }
  else {
    client.stop();
    return;
  }
  client.flush();
  client.println(enviar);
  delay(10);


}*/
checarUmidade();
checarHora();
printTime();
molhar();
conectar();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void conectar()
  {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Comunicacao Ok");
    String op = client.readString();
    Serial.println(op);
    if (op == "Molhar")
    {
      digitalWrite(saida_pos, HIGH);
      digitalWrite(saida_neg, HIGH);
      //fazer algo
      Serial.println("Voce apertou o botao Molhar");
      enviar = "Molhando";
    }
    if (op == "Parar")
    {
      digitalWrite(saida_pos, LOW);
      digitalWrite(saida_neg, LOW);
      //faz algo mágico
      Serial.println("Voce apertou o botao Parar");
      enviar = "Parando";
    }

    client.println(enviar);
    client.stop();
  }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  void molhar()
  {
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
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
