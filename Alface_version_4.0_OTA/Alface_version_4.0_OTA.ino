/**
 * Projeto versao 4.0.1_OTA compilada em 31 de dezembro de 2018 as 22:43
 * O sistema foi criado por Luis Ricardo 
 * Por favor respeite os direitos autorais 
 * O sistema consiste de processamentos de sensores e transmissão via rede 
 * utilizando o protocolo de comunicação 802.11 b/g/n
 */
#include <DHTesp.h>//Sensor dht umidade e temperatura
#include <DS1302.h>//Relogio Rtc 
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#define DHTTYPE DHT11
/**
 * Definindo constantes para os pinos 
 */
const int DHTPIN = D8; // pino que estamos conectado
const int SAIDARELE1 =D2;
const int SAIDARELE2 =D3;
const int entradaFot = D4; //Entrada fotocelula
const int kCePin   = D5;  // Chip Enable
const int kIoPin   = D6;  // Input/Output
const int kSclkPin = D7;  // Serial Clock
const int entradaUmiTemp = D8;//entrada do DHT pino data
const int entradaUmidade_berco1 = A0;//Entrada do sendsor de umidade do berÃ§o 1 atualmente esta no berço 2 sendo as cores de conexão o verde e branco verde
//int entradaUmidade_berco2 = A1;//Entrada do sendsor de umidade do berÃ§o 1
//int entradaUmidade_berco3 = A2;//Entrada do sendsor de umidade do berÃ§o 1

/**
 * Definindo endereços IP
 */
IPAddress ip = IPAddress(192, 168, 1, 254);
IPAddress gw = IPAddress(192, 168, 1, 1);
IPAddress sn = IPAddress(255, 255, 255, 0);
const char* ssid = "Zhone_BD30";
const char* password = "znid307322928";
WiFiServer server(5600);
/**
 * Definindo variaveis globais
 */
int leituraUmidade=0;
int valorUmidade1 = 0;
int valorUmidade2 = 0;
int valorUmidade3 = 0;
bool chora = false;
bool molhou = false;
bool diaNoite = false;
String enviar = "";
/**
 * Definindo assinatura das funçoes
 */
void conectar();
void molhar();
void checarUmidade();
void MostrarTempUmid();
void checarHora();
void printTime();
void dia();
String dayAsString(const Time::Day day);
/**
 * Criando objeto DHT sensor de umidade e temperatura
 */
DHTesp dht;
/**
 * Criando ojeto relogio definindo pinos
 * const int kCePin   = D5;  // Chip Enable
 * const int kIoPin   = D6;  // Input/Output
 * const int kSclkPin = D7;  // Serial Clock
 */
DS1302 rtc(kCePin, kIoPin, kSclkPin);
/**
 * Entrando no modo Setup
 */
void setup() {
/**
 * Gravação do relogio 
 * Esta deve ser feita uma vez apenas
 * rtc.writeProtect(false);
 * rtc.halt(false);
 * Crie um novo obejeto para mudar a daa e a hora.
 * Time t(2018, 12, 31, 22, 52, 50, Time::kSunday);
 * Selecione a hora e data do objeto criado anteriormente.
 * rtc.time(t);
 */

 /**
  * Comunicação serial a 115200 bits por segundos
  */
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  /**
   * Configurando o wifi
   */
  WiFi.config(ip, gw, sn);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
   while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  // Port defaults to 8266
 // ArduinoOTA.setPort(5600);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("Projeto-Alface versão 4.0");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
  Serial.println("WiFi conectado");
  server.begin();
  Serial.println("Servidor Iniciado");
  pinMode(SAIDARELE1, OUTPUT);
  pinMode(SAIDARELE2, OUTPUT);
  digitalWrite(SAIDARELE1, HIGH);
  digitalWrite(SAIDARELE2, HIGH);
  pinMode(entradaFot, INPUT);
  pinMode(entradaUmidade_berco1 , INPUT);
  dht.setup(DHTPIN, DHTesp::DHT11); // Connect DHT sensor to 4
}

void loop() 
{
  ArduinoOTA.handle();
    checarUmidade();
    MostrarTempUmid();
    printTime();
    molhar();
    checarHora();
    dia();
  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void dia()
{
  diaNoite = digitalRead(entradaFot);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void conectar()
{
WiFiClient client = server.available();
  if (!client)
  {
  Serial.println("Sem clientes disponiveis");
    //Se nÃ£o houver nenhum cliente podemos retornar pois nÃ£o hÃ¡ nada a fazer
    return;
  }
  else {
    while (!client.available())
    {
      delay(100);
    }
    String op = client.readString();

    Serial.println(op);
    if (op == "abrirValvula")
    {
      digitalWrite(SAIDARELE1, LOW);
      digitalWrite(SAIDARELE2, LOW);
      //fazer algo
      Serial.println("Voce apertou o botao Molhar");
      enviar = "Molhando";
    }
    if (op == "fecharValvula")
    {
      digitalWrite(SAIDARELE1, HIGH);
      digitalWrite(SAIDARELE2, HIGH);
      //faz algo mÃ¡gico
      Serial.println("Voce apertou o botao Parar");
      enviar = "Parando";
    }
    if (op == "lerTemperatura")
    {
      enviar = "TesteTemperatura";
    }
    if (op == "lerUmidade")
    {
      Serial.println("Voce apertou o botao para ler umidade");
      enviar = (String)leituraUmidade;
    }
    if (op == "lerUmidadeAr")
    {
      enviar = "TesteUmidadeAr";
    }
    if (op == "lerLuminosidade")
    {
      enviar = "TesteLuminosidade";
    }
    if (op == "lerHora")
    {
      enviar = "TesteUmidade";
    }
    client.print(enviar);
    client.stop();
  }


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
  leituraUmidade = analogRead(entradaUmidade_berco1);
  if (leituraUmidade <= 1023 && leituraUmidade >= 682) {
    valorUmidade1 = 2;
  } else {
    if (leituraUmidade <= 681 && leituraUmidade >= 341) {
      valorUmidade1 = 1;
    }
    else {
      if (leituraUmidade <= 340 && leituraUmidade >= 0) {
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

