#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial
#include <WiFi.h>

#include <BlynkSimpleEsp32.h>

#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>

#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "";
char pass[] = "";

BlynkTimer timer;

Adafruit_BMP085 bmp;
float t, p, a;

int suelo = 33;
int lectura;

#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

float td, hd;

void sendSensor(){
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, p);
  Blynk.virtualWrite(V2, a);

  Blynk.virtualWrite(V3, td);

  Blynk.virtualWrite(V4, hd);
  Blynk.virtualWrite(V5, lectura);
}


void setup(){
  Serial.begin(115200);

  dht.begin();
    
  if (!bmp.begin()) {
    Serial.println("Error en el sensor");
    while (1); //bucle infinito
  }
  

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);

}

void loop(){
  //Barometro
  t = bmp.readTemperature();
  p = bmp.readPressure() / 100;
  a = bmp.readAltitude(101700);

  //Humedad
  lectura = analogRead(suelo);

  //DTH11
  td = dht.readTemperature();
  hd = dht.readHumidity();



  Blynk.run();
  timer.run();
}

