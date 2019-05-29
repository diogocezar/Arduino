#include <SPI.h>
#include <Wire.h>
//#include "DHT.h"
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
#define DHTPIN 2
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(OLED_RESET);


void setup() {
Serial.begin(9600);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//dht.begin();
}

void loop() {

//int h = dht.readHumidity();

// Read temperature as Fahrenheit (isFahrenheit = true)
//int f = dht.readTemperature(true);

display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.print("TEMP "); display.print("f"); display.println("F");
display.setTextSize(2);
display.setTextColor(WHITE);
display.print("Humid: "); display.print("h"); display.println("%");
display.display();
delay(1000);

}
