#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Stepper.h>


#define DHTPIN 9       // Pin del sensor DHT11
#define DHTTYPE DHT11  // Tipo de sensor DHT (DHT11 en este caso)

#define TRIGGER_PIN 4  // Pin del trigger del sensor ultrasónico
#define ECHO_PIN 5     // Pin del echo del sensor ultrasónico

#define STEPS 200      // Número de pasos por revolución del motor paso a paso
#define MOTOR_PIN_1 6  // Pin 1 del motor paso a paso
#define MOTOR_PIN_2 7  // Pin 2 del motor paso a paso
#define MOTOR_PIN_3 8  // Pin 3 del motor paso a paso
#define MOTOR_PIN_4 9  // Pin 4 del motor paso a paso

// Inicializar el objeto DHT y el objeto LCD
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

Stepper stepper(STEPS, MOTOR_PIN_1, MOTOR_PIN_3, MOTOR_PIN_2, MOTOR_PIN_4);

//inicializamos las variables para guardar los valores y mandar a labview
float var1;
float var2;

unsigned long msegi = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();

  lcd.begin(16, 2);

  // Configurar los pines del sensor ultrasónico
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  //Establecer la velocidad del motor paso a paso
  stepper.setSpeed(100);  // Ajusta esta velocidad según tus necesidades
}


void loop() {
  //leemos los valores y los guardamos en sus respectivas variables

  float temperature = dht.readTemperature();
  float distance = readDistance();

  var1 = temperature; 
  var2 = distance;

  //Mostrar los valores en el LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(temperature);
  lcd.print("C ");
 // lcd.setCursor(0, 1);
  lcd.print("C: ");
  lcd.print(distance);
  lcd.print("cm");

  // Comparar la temperatura y la distancia
  if (temperature > distance) {
    // Gira el motor en sentido horario
    stepper.step(100);  // Ajusta el número de paso
    lcd.setCursor(0, 1);
    lcd.print("Motor: Horario ");
  } else if (distance > temperature) {
    // Gira el motor en sentido antihorario
    stepper.step(-100);  // Ajusta el número de pasos
    lcd.setCursor(0, 1);
    lcd.print("Motor: Antihorario");
  } else {
    // No hacer nada
    lcd.setCursor(0, 1);
    lcd.print("Motor: Detenido   ");
  }

  delay(2000);  // Ajusta este valor según tus necesidades

  //miramos cuanto tiempo ha pasado desde que se ejecuto el programa
  unsigned long msegf = millis();

  if (msegf - msegi >= 100) {
    msegi = msegf;
    //mandamos los datos leidos a labview
    Serial.print(var1);
    Serial.print(',');
    Serial.println(var2);
  }
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
