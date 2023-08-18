#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>

Adafruit_BMP085 bmp;

//Agregamos ls librerias de cristal liquido
#include <LiquidCrystal.h>
//Inicializamos los pines conectados de la pantalla de cristal liquido al esp32
LiquidCrystal lcd(13,23,5,18,19,12);
/*
                  RS,E,D4,D5,D6,D7
  A, VDD to 3.3v
  K, VSS, RW to GND
  V0 to Pot Out
*/
 

float t = 0, p = 0, a = 0;

void setup() {
  Serial.begin(115200);
  lcd.begin(16,2);
  if (!bmp.begin()) {
  Serial.println("Error en el sensor");
  while (1); //bucle infinito
  }
}
void loop() {
  lcd.setCursor(0,0);
  
  t = bmp.readTemperature();
  p = bmp.readPressure() / 100;
  a = bmp.readAltitude(101700); // 1017 cambia segun a la localidad
  //Serial.print("Temperatura:");
  //Serial.println(t);
  Serial.println("Temperatura: " + String(t) + " *C"); //String convierte t a cadena
  Serial.println("Presion: " + String(p) + "  hPa");
  Serial.println("Altitud: " + String(a) + " m");

  lcd.println("Temperatura: " + String(t) + " *C "); 
  lcd.println("Presion: " + String(p) + "  hPa ");
  lcd.setCursor(0,1);
  lcd.println("Altitud: " + String(a) + " m");
  //lcd.scrollDisplayLeft();

  delay(2000);

  for (int i = 0; i < 16; i++) {
    lcd.scrollDisplayLeft();
    delay(100);
  }

}