#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  
byte ip[] = { 192, 168, 0, 254 };    
byte gateway[] = { 192, 168, 0, 1 };
byte subnet[] = { 255, 255, 255, 0 };
EthernetServer server = EthernetServer(5600);
char r;
void setup()
{
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.begin(9600);
}
void loop()
{
  EthernetClient client = server.available();
  if(client)
  {
    Serial.println("cliente conectado");
  }
 
  client.stop();
  
  //int r= rand()*1000;
   // server.println(r);
  
}
