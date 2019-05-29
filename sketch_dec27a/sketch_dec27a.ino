#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "VENTURE 11";
const char* pass = "12345678";

WiFiClient clientx;
const int trigPin = 8;  //Digital port D5
const int echoPin = 9;  //Digital port D6

long duration;
float distance;
float Mdistance;
float MAX_HEIGHT = 0;


void setup() {
 wdt_disable();
  Serial.begin(115200);                                  //Serial connection
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);

  WiFi.begin("Teste", "1qaz2wsx");   //WiFi connection
  Serial.println("Setup iniated");
  while (WiFi.status() != 3) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
    Serial.print("WIFI STATUS : ");
    Serial.println(String(WiFi.status()));
  }
  Serial.println(String(WiFi.status()));
}

void loop() {
  Serial.println(String(WiFi.status()));
  if (WiFi.status() != 3)
  {
    WiFi.begin("Teste", "1qaz2wsx");   //WiFi connection
    while (WiFi.status() != 3)
    {
      Serial.println("Waiting for connection");
    }
  }
  else
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance = (duration * 0.034) / 2;


    if (MAX_HEIGHT == 0) {
      //MAX_HEIGHT = distance;
      Serial.print("Max height has been set to ");
      //Serial.print(distance);
      Serial.println(" cm");
      Serial.println("Waiting for 5 seconds...");
      delay(5000);
    } else {
      Serial.print("Distance:\n");
      Serial.print(distance);
      Serial.print("cm\n");
      Serial.print("Distance:\n");
      Serial.print(distance / 100);
      Serial.print("m\n");
      delay(1000);


    }

    HTTPClient http;
    String Data = "x=" + (String)distance + "&y=" + (String)MAX_HEIGHT + "&z=0";
    //String Data = "x=Finally&y=Did&z=it;)";
    http.begin("http://testingblahblah.000webhostapp.com/IOTCON.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int sent = http.POST(Data);
    Serial.println(sent);
    String httpPayload = http.getString();
    Serial.println(httpPayload);
    if (sent > 0)
    {
      Serial.println("Message has been sent");
    } else {
      Serial.println("unable to send data");
    }
    delay(20000);

  }
}
