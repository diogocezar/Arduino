////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Arquivo:   MQTT_WiFiManager_Rele.ino
//Tipo:      Exemplo de uso das bibliotecas WiFiManager e PubSubClient para ESP8266 na IDE do Arduino
//Autor:     Marco Rabelo para o canal Infortronica Para Zumbis (www.youtube.com/c/InfortronicaParaZumbis)
//Descricao: Curso de ESP8266 - Utilizando MQTT e gerenciador de wifi para controlar um rel�.
//Video:     https://youtu.be/oX4ttJEULmA
////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
Equivalencia das saidas Digitais entre NodeMCU e ESP8266 (na IDE do Arduino)
NodeMCU - ESP8266
D0 = 16;
D1 = 5;
D2 = 4;
D3 = 0;
D4 = 2;
D5 = 14;
D6 = 12;
D7 = 13;
D8 = 15;
D9 = 3;
D10 = 1;
*/

#include <FS.h>                 //Esta precisa ser a primeira refer�ncia, ou nada dar� certo e sua vida ser� arruinada. kkk
#include <ESP8266WiFi.h>        //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>        //https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h>        //https://github.com/bblanchon/ArduinoJson
#include <PubSubClient.h>
#include <EEPROM.h>

#define DEBUG                   //Se descomentar esta linha vai habilitar a 'impress�o' na porta serial

//Coloque os valores padr�es aqui, por�m na interface eles poder�o ser substitu�dos.
#define servidor_mqtt             "0.0.0.0"  //URL do servidor MQTT
#define servidor_mqtt_porta       "1883"  //Porta do servidor (a mesma deve ser informada na vari�vel abaixo)
#define servidor_mqtt_usuario     "general"  //Usu�rio
#define servidor_mqtt_senha       "general"  //Senha
#define mqtt_topico_sub           "esp8266/pincmd"    //T�pico para subscrever o comando a ser dado no pino declarado abaixo

//Declara��o do pino que ser� utilizado e a mem�ria alocada para armazenar o status deste pino na EEPROM
#define pino                      2                   //Pino que executara a acao dado no topico "esp8266/pincmd" e ter� seu status informado no t�pico "esp8266/pinstatus"
#define memoria_alocada           4                   //Define o quanto sera alocado na EEPROM (valores entre 4 e 4096 bytes)

WiFiClient espClient;                                 //Inst�ncia do WiFiClient
PubSubClient client(espClient);                       //Passando a inst�ncia do WiFiClient para a inst�ncia do PubSubClient

uint8_t statusAnt   =             0;                  //Vari�vel que armazenar� o status do pino que foi gravado anteriormente na EEPROM
bool precisaSalvar  =             false;              //Flag para salvar os dados

//Fun��o para imprimir na porta serial
void imprimirSerial(bool linha, String mensagem){
  #ifdef DEBUG
    if(linha){
      Serial.println(mensagem);
    }else{
      Serial.print(mensagem);
    }
  #endif
}

//Fun��o de retorno para notificar sobre a necessidade de salvar as configura��es
void precisaSalvarCallback() {
  imprimirSerial(true, "As configuracoes tem que ser salvas.");
  precisaSalvar = true;
}

//Fun��o que reconecta ao servidor MQTT
void reconectar() {
  //Repete at� conectar
  while (!client.connected()) {
    imprimirSerial(false, "Tentando conectar ao servidor MQTT...");
    
    //Tentativa de conectar. Se o MQTT precisa de autentica��o, ser� chamada a fun��o com autentica��o, caso contr�rio, chama a sem autentica��o. 
    bool conectado = strlen(servidor_mqtt_usuario) > 0 ?
                     client.connect("ESP8266Client", servidor_mqtt_usuario, servidor_mqtt_senha) :
                     client.connect("ESP8266Client");

    if(conectado) {
      imprimirSerial(true, "Conectado!");
      //Subscreve para monitorar os comandos recebidos
      client.subscribe(mqtt_topico_sub, 1); //QoS 1
    } else {
      imprimirSerial(false, "Falhou ao tentar conectar. Codigo: ");
      imprimirSerial(false, String(client.state()).c_str());
      imprimirSerial(true, " tentando novamente em 5 segundos");
      //Aguarda 5 segundos para tentar novamente
      delay(5000);
    }
  }
}

//Fun��o que verifica qual foi o �ltimo status do pino antes do ESP ser desligado
void lerStatusAnteriorPino(){
  EEPROM.begin(memoria_alocada);  //Aloca o espaco definido na memoria
  statusAnt = EEPROM.read(0);     //Le o valor armazenado na EEPROM e passa para a vari�vel "statusAnt"
  if(statusAnt > 1){
    statusAnt = 0;                //Provavelmente � a primeira leitura da EEPROM, passando o valor padr�o para o pino.
    EEPROM.write(0,statusAnt);
  }
  digitalWrite(pino, statusAnt);
  EEPROM.end();
}

//Fun��o que grava status do pino na EEPROM
void gravarStatusPino(uint8_t statusPino){
  EEPROM.begin(memoria_alocada);
  EEPROM.write(0, statusPino);
  EEPROM.end();
}

//Fun��o que ser� chamada ao receber mensagem do servidor MQTT
void retorno(char* topico, byte* mensagem, unsigned int tamanho) {
  //Convertendo a mensagem recebida para string
  mensagem[tamanho] = '\0';
  String strMensagem = String((char*)mensagem);
  strMensagem.toLowerCase();
  //float f = s.toFloat();
  
  imprimirSerial(false, "Mensagem recebida! Topico: ");
  imprimirSerial(false, topico);
  imprimirSerial(false, ". Tamanho: ");
  imprimirSerial(false, String(tamanho).c_str());
  imprimirSerial(false, ". Mensagem: ");
  imprimirSerial(true, strMensagem);

  //Executando o comando solicitado
  imprimirSerial(false, "Status do pino antes de processar o comando: ");
  imprimirSerial(true, String(digitalRead(pino)).c_str());
  
  if(strMensagem == "liga"){
    imprimirSerial(true, "Colocando o pino em stado ALTO...");
    digitalWrite(pino, HIGH);
    gravarStatusPino(HIGH);
  }else if(strMensagem == "desliga"){
    imprimirSerial(true, "Colocando o pino em stado BAIXO...");
    digitalWrite(pino, LOW);
    gravarStatusPino(LOW);
  }else{
    imprimirSerial(true, "Trocando o estado do pino...");
    digitalWrite(pino, !digitalRead(pino));
    gravarStatusPino(digitalRead(pino));
  }
  
  imprimirSerial(false, "Status do pino depois de processar o comando: ");
  imprimirSerial(true, String(digitalRead(pino)).c_str());
}

//Fun��o inicial (ser� executado SOMENTE quando ligar o ESP)
void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
  imprimirSerial(true, "...");

  //Fazendo o pino ser de sa�da, pois ele ir� "controlar" algo.
  pinMode(pino, OUTPUT);
  
  //Formatando a mem�ria interna
  //(descomente a linha abaixo enquanto estiver testando e comente ou apague quando estiver pronto)
  //SPIFFS.format();

  //Iniciando o SPIFSS (SPI Flash File System)
  imprimirSerial(true, "Iniciando o SPIFSS (SPI Flash File System)");
  if (SPIFFS.begin()) {
    imprimirSerial(true, "Sistema de arquivos SPIFSS montado!");
    if (SPIFFS.exists("/config.json")) {
      //Arquivo de configura��o existe e ser� lido.
      imprimirSerial(true, "Abrindo o arquivo de configuracao...");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        imprimirSerial(true, "Arquivo de configuracao aberto.");
        size_t size = configFile.size();
        
        //Alocando um buffer para armazenar o conte�do do arquivo.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
            //Copiando as vari�veis salvas previamente no aquivo json para a mem�ria do ESP.
            imprimirSerial(true, "arquivo json analisado.");
            strcpy(servidor_mqtt, json["servidor_mqtt"]);
            strcpy(servidor_mqtt_porta, json["servidor_mqtt_porta"]);
            strcpy(servidor_mqtt_usuario, json["servidor_mqtt_usuario"]);
            strcpy(servidor_mqtt_senha, json["servidor_mqtt_senha"]);
            strcpy(mqtt_topico_sub, json["mqtt_topico_sub"]);

        } else {
          imprimirSerial(true, "Falha ao ler as configuracoes do arquivo json.");
        }
      }
    }
  } else {
    imprimirSerial(true, "Falha ao montar o sistema de arquivos SPIFSS.");
  }
  //Fim da leitura do sistema de arquivos SPIFSS

  //Par�metros extras para configura��o
  //Depois de conectar, parameter.getValue() vai pegar o valor configurado.
  //Os campos do WiFiManagerParameter s�o: id do par�metro, nome, valor padr�o, comprimento
  WiFiManagerParameter custom_mqtt_server("server", "Servidor MQTT", servidor_mqtt, 40);
  WiFiManagerParameter custom_mqtt_port("port", "Porta", servidor_mqtt_porta, 6);
  WiFiManagerParameter custom_mqtt_user("user", "Usuario", servidor_mqtt_usuario, 20);
  WiFiManagerParameter custom_mqtt_pass("pass", "Senha", servidor_mqtt_senha, 20);
  WiFiManagerParameter custom_mqtt_topic_sub("topic_sub", "Topico para subscrever", mqtt_topico_sub, 30);

  //Inicializa��o do WiFiManager. Uma vez iniciado n�o � necess�rio mant�-lo em mem�ria.
  WiFiManager wifiManager;

  //Definindo a fun��o que informar� a necessidade de salvar as configura��es
  wifiManager.setSaveConfigCallback(precisaSalvarCallback);
  
  //Adicionando os par�metros para conectar ao servidor MQTT
  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_mqtt_user);
  wifiManager.addParameter(&custom_mqtt_pass);
  wifiManager.addParameter(&custom_mqtt_topic_sub);

  //Busca o ID e senha da rede wifi e tenta conectar.
  //Caso n�o consiga conectar ou n�o exista ID e senha,
  //cria um access point com o nome "AutoConnectAP" e a senha "senha123"
  //E entra em loop aguardando a configura��o de uma rede WiFi v�lida.
  if (!wifiManager.autoConnect("AutoConnectAP", "senha123")) {
    imprimirSerial(true, "Falha ao conectar. Excedeu o tempo limite para conexao.");
    delay(3000);
    //Reinicia o ESP e tenta novamente ou entra em sono profundo (DeepSleep)
    ESP.reset();
    delay(5000);
  }

  //Se chegou at� aqui � porque conectou na WiFi!
  imprimirSerial(true, "Conectado!! :)");

  //Lendo os par�metros atualizados
  strcpy(servidor_mqtt, custom_mqtt_server.getValue());
  strcpy(servidor_mqtt_porta, custom_mqtt_port.getValue());
  strcpy(servidor_mqtt_usuario, custom_mqtt_user.getValue());
  strcpy(servidor_mqtt_senha, custom_mqtt_pass.getValue());
  strcpy(mqtt_topico_sub, custom_mqtt_topic_sub.getValue());

  //Salvando os par�metros informados na tela web do WiFiManager
  if (precisaSalvar) {
    imprimirSerial(true, "Salvando as configuracoes");
  DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["servidor_mqtt"] = servidor_mqtt;
    json["servidor_mqtt_porta"] = servidor_mqtt_porta;
    json["servidor_mqtt_usuario"] = servidor_mqtt_usuario;
    json["servidor_mqtt_senha"] = servidor_mqtt_senha;
    json["mqtt_topico_sub"] = mqtt_topico_sub;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      imprimirSerial(true, "Houve uma falha ao abrir o arquivo de configuracao para incluir/alterar as configuracoes.");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
  }

  imprimirSerial(false, "IP: ");
  imprimirSerial(true, WiFi.localIP().toString());

  //Informando ao client do PubSub a url do servidor e a porta.
  int portaInt = atoi(servidor_mqtt_porta);
  client.setServer(servidor_mqtt, portaInt);
  client.setCallback(retorno);
  
  //Obtendo o status do pino antes do ESP ser desligado
  lerStatusAnteriorPino();
}

//Fun��o de repeti��o (ser� executado INFINITAMENTE at� o ESP ser desligado)
void loop() {
  if (!client.connected()) {
    reconectar();
  }
  client.loop();
}
