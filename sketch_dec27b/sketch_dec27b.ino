#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

// the Arduino's static IP address
IPAddress ip(192, 168, 0, 177);    
char ssid[] = "Teste";    
char pass[] = "1qaz2wsx";
int status = WL_IDLE_STATUS;
 
void setup()
{  
  Serial.begin(9600); 
  WiFi.config(ip);
 
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
 
    // wait 10 seconds for connection:
    delay(10000);
  }
 
// print your WiFi shield's IP address:
 IPAddress ip = WiFi.localIP(); 
 Serial.print("IP Address: ");
 Serial.println(IpAddress2String(ip)); 
}
 
void loop () {}
 
String IpAddress2String(const IPAddress& ipAddress)
{
    return String(ipAddress[0]) + String(".") +\
      String(ipAddress[1]) + String(".") +\
      String(ipAddress[2]) + String(".") +\
      String(ipAddress[3]) ;
}
