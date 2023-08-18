#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>
#include "ThingSpeak.h"
const char* ssid = "dch";
const char* password = "xd123456";
unsigned long ID_canal = 2165489; //id del canal en thingspeak
const char* KEY = "OO2SMXZ7LV1ICG5N"; //Key del canal
WiFiClient cliente;
Adafruit_BMP085 bmp;
float t = 0, p = 0, a = 0, p0 = 0, h = 0;
void setup() {
  Serial.begin(115200);
  if (!bmp.begin()) {
    Serial.println("Error en el sensor");
    while (1); //bucle infinito
  }
  p0 = bmp.readAltitude() / 100; //p -> Hp
  WiFi.begin(ssid, password); //agregamos los credenciales de nuestra red
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conectado al WiFi");
  ThingSpeak.begin(cliente);
  delay(5000);
}
void loop() {
  t = bmp.readTemperature();
  p = bmp.readPressure();
  a = bmp.readAltitude(101700); //1153.1 cambia segun a la localidad

  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, p);
  ThingSpeak.setField(3, a);
  ThingSpeak.writeFields(ID_canal, KEY);
  Serial.println("Datos enviados correctamente!");
  delay(15000); //es el tiempo de retardo para comunicarse con thingspeak
}