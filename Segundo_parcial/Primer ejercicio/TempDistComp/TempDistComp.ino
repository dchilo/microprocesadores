#define BLYNK_TEMPLATE_ID "TMPL2evArSOfE"
#define BLYNK_TEMPLATE_NAME "TemperaturaDistancia"
#define BLYNK_AUTH_TOKEN "9zP0vR7TfsjgPdWaOJHs_jWD5hvEmbTO"

#define BLYNK_PRINT Serial
#include <WiFi.h>

#include <BlynkSimpleEsp32.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Stepper.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "dch";
char pass[] = "xd123456";

BlynkTimer timer;

#define DHTPIN 27      // Pin del sensor DHT11
#define DHTTYPE DHT11  // Tipo de sensor DHT (DHT11 en este caso)

#define TRIGGER_PIN 4  // Pin del trigger del sensor ultrasónico
#define ECHO_PIN 5     // Pin del echo del sensor ultrasónico

#define STEPS 200       // Número de pasos por revolución del motor paso a paso
#define MOTOR_PIN_1 26  // Pin 1 del motor paso a paso
#define MOTOR_PIN_2 25  // Pin 2 del motor paso a paso
#define MOTOR_PIN_3 33  // Pin 3 del motor paso a paso
#define MOTOR_PIN_4 32  // Pin 4 del motor paso a paso

// Inicializar el objeto DHT y el objeto LCD
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Inicializar el objeto Stepper para controlar el motor paso a paso
Stepper stepper(STEPS, MOTOR_PIN_1, MOTOR_PIN_3, MOTOR_PIN_2, MOTOR_PIN_4);

float temperature, distance;
String info;

void sendSensor(){
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, distance);
  Blynk.virtualWrite(V2, info);
}

void setup() {

  // Inicializar los puertos serie, el LCD y el sensor DHT
  Serial.begin(115200);
  lcd.begin(16, 2);
  dht.begin();

  // Configurar los pines del sensor ultrasónico
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Establecer la velocidad del motor paso a paso
  stepper.setSpeed(100);  // Ajusta esta velocidad según tus necesidades

  //Inicializar Blynk

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, sendSensor);
}


void loop() {
  // Leer la temperatura y la humedad
  temperature = dht.readTemperature();

  // Leer la distancia
  distance = readDistance();

  // Mostrar los valores en el LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print("cm");

  // Comparar la temperatura y la distancia
  if (temperature > distance) {
    // Gira el motor en sentido horario
    stepper.step(100);  // Ajusta el número de pasos según tus necesidades
    lcd.setCursor(0, 1);
    lcd.print("Motor: Horario ");
    info = "Motor: Horario";
  } else if (distance > temperature) {
    // Gira el motor en sentido antihorario
    stepper.step(-100);  // Ajusta el número de pasos según tus necesidades
    lcd.setCursor(0, 1);
    lcd.print("Motor: Antihorario");
    info = "Motor: Antihorario";
  } else {
    // No hacer nada
    lcd.setCursor(0, 1);
    lcd.print("Motor: Detenido");
    info = "Motor: Detenido";
  }


  Blynk.run();
  timer.run();

  delay(2000);  // Ajusta este valor según tus necesidades
}



float readDistance() {
  // Generar un pulso de 10 µs en el pin del trigger
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Leer el tiempo de respuesta en el pin del echo
  float duration = pulseIn(ECHO_PIN, HIGH);

  // Calcular la distancia en centímetros
  float distance = duration * 0.034 / 2;

  return distance;
}
