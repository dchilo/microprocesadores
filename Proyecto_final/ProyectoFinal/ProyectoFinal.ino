#define BLYNK_TEMPLATE_ID "TMPL2i-3Sau1H"
#define BLYNK_TEMPLATE_NAME "ProyectoMeteorologia"
#define BLYNK_AUTH_TOKEN "U_o_AkwCDFz4WDP_SElx9BxdEXhGrZQN"

#include <CTBot.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WebServer.h>

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

WebServer server(80);

// Configuracion de la red WiFi
char* ssid = "dch";
char* password = "xd123456";

// Configuracion del Bot de Telegram
String token = "6207934903:AAFG7LUHSymR2YDVgTYVQa2FNZ2tY94VfZc";
const int64_t telegramId = 803120820;

// Configuraciones de los pines de los sensores
#define DHTPIN 14
#define BMP_SDA 21
#define BMP_SCL 22
#define ONEWIRE_PIN 19

// Inicializando de los sensores
DHT dht(DHTPIN, DHT11);
Adafruit_BMP085 bmp;
OneWire oneWire(ONEWIRE_PIN);
DallasTemperature ds18b20(&oneWire);

int suelo = 33;

CTBot mybot;

float humidity, temperature, pressure, temperatureDs18b20, temperatureBMP, altitude;
int sueloLectura;
String Data, savedData, lastSavedData, ayuda;
float liveh, livet, livep, livetds, livebmp, livea;
int lives;
bool isMeasuring;

BlynkTimer timer;

int luz = 18;
bool luzEncendida = false;
int luzBlynk;

float tiempo = 0;


void sendSensor(){
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, pressure);

  Blynk.virtualWrite(V3, altitude);

  Blynk.virtualWrite(V4, temperatureBMP);
  Blynk.virtualWrite(V5, sueloLectura);
  Blynk.virtualWrite(V6, temperatureDs18b20);

  Blynk.virtualWrite(V7, luzBlynk);
}



void handleSave() {
  lastSavedData = "Temperatura DHT: " + String(temperature) + "  C, " +"Humedad: " + String(humidity) + " %, " + "Presion atmosferica: " + String(pressure) + " hPa, " + "Altitud: " + String(altitude) + " m, " + "Temperatura BMP: " + String(temperatureBMP) + " C, " + "Humedad del suelo: " + String(sueloLectura) + ", " + "Temperatura del agua: " + String(temperatureDs18b20) + " C";
  savedData += lastSavedData + "<br>";
  server.sendHeader("Location", "/");
  server.send(303);
}


void handleView() {
  isMeasuring = true;
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleRoot() {
  String html = "<html><head>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; }";
  html += "h1 { color: #333; }";
  html += "h2 { color: #666; }";
  html += "p { margin-bottom: 10px; }";
  html += "b { font-weight: bold; }";
  html += "span { color: #888; }";
  html += "form { margin-top: 20px; }";
  html += "</style>";
  html += "<title>Datos</title>";

  // Mostrar los datos en una tabla
  html += "<body><h1>Servidor en ESP32</h2>";
  html += "<h2>Datos:</h2>";

  html += "<p><b>Temperatura DHT:</b> <span id='temperature'>" + String(livet) + " &deg;C</span></p>";
  html += "<p><b>Humedad:</b> <span id='humedad'>" + String(liveh) + " %</span></p>";
  html += "<p><b>Presion atmosferica:</b> <span id='presion'>" + String(livep) + " hPa</span></p>";
  html += "<p><b>Altitud:</b> <span id='altitud'>" + String(livea) + " m</span></p>";
  html += "<p><b>Temperatura BMP:</b> <span id='temperaturebmp'>" + String(livebmp) + " &deg;C</span></p>";
  html += "<p><b>Humedad del suelo:</b> <span id='humedadsuelo'>" + String(lives) + "</span></p>";
  html += "<p><b>Temperatura del agua:</b> <span id='temperature'>" + String(livetds) + " &deg;C</span></p>";

  html += "<form action=\"/start\">";
  html += "<input type=\"submit\" value=\"Actualizar\">";
  html += "</form>";
  html += "<form action=\"/save\">";
  html += "<input type=\"submit\" value=\"Guardar\">";
  html += "</form>";

  html += "<h3>Historial de Datos Guardados:</h3>";
  html += "<p>" + savedData + "</p>";

  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Bot...");

  pinMode(luz, OUTPUT);
    
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red Wi-Fi...");
  }

  Serial.println("Conexión Wi-Fi establecida");
  Serial.print("Dirección IP del servidor: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/save", handleSave);
  server.on("/start", handleView);
  server.begin();
  Serial.println("Servidor iniciado");


  mybot.wifiConnect(ssid, password);

  mybot.setTelegramToken(token);

  dht.begin();
    
  if (!bmp.begin()) {
    Serial.println("Error en el sensor");
    while (1); //bucle infinito
  }

  if (mybot.testConnection()) {
    Serial.println("\n Conectado");
  } else {
    Serial.println("\n No conectado");
  }

  ayuda = "Comandos para el bot:\n";
  ayuda += "Para la temperatura de sensor DHT11: temperatura dht\n";
  ayuda += "Para la humedad del sensor DHT11: humedad\n";
  ayuda += "Para la temperatura del sensor BMP180: temperatura bmp\n";
  ayuda += "Para la altitud del sensor BMP180: altitud\n";
  ayuda += "Para la presion del sensor BMP180: presion\n";
  ayuda += "Para la humedad del suelo: suelo\n";
  ayuda += "Para la temperatura del sensor DS18B20\n";
  ayuda += "Para todos los datos: datos";

  Blynk.begin(auth, ssid, password);
  timer.setInterval(1000L, sendSensor);

}

void loop() {
  TBMessage msg;

  // Lectura de los datos de los sensores
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  temperatureBMP = bmp.readTemperature();
  altitude = bmp.readAltitude(101700);
  pressure = bmp.readPressure() / 100.0;

  sueloLectura = analogRead(suelo);

  ds18b20.requestTemperatures();
  temperatureDs18b20 = ds18b20.getTempCByIndex(0);

  if (isMeasuring) {
    liveh = humidity;
    livet = temperature;
    livep = pressure;
    livetds = temperatureDs18b20;
    livebmp = temperatureBMP;
    livea = altitude;
    lives = sueloLectura;
  }

  // Control de la luz
  if (luzEncendida == true) {
    digitalWrite(luz, HIGH);
    luzBlynk = 255;
  } else {
    digitalWrite(luz, LOW);
    luzBlynk = 0;
  }

  // Datos
  Data = "Temperatura DHT: " + String(temperature) + " °C\n";
  Data += "Humedad: " + String(humidity) + "%\n";
  Data += "Presión atmosférica: " + String(pressure) + " hPa\n";
  Data += "Altitud: " + String(altitude) + " m\n";
  Data += "Temperatura BMP: " + String(temperatureBMP) + " °C\n";
  Data += "Humedad del suelo: " + String(sueloLectura) + "\n";
  Data += "Temperatura del agua: " + String(temperatureDs18b20) + " °C\n";


  // Consultas por Telegram
  if (CTBotMessageText == mybot.getNewMessage(msg)) {
    Serial << "Mensaje: " << msg.sender.firstName << " - " << msg.text << "\n";
    
    if (msg.text.equalsIgnoreCase("temperatura dht")) {
      Serial.print("Temperatura DHT");
      mybot.sendMessage(msg.sender.id, String(temperature) + "°C");
    }
    if (msg.text.equalsIgnoreCase("humedad")) {
      Serial.print("humedad DHT");
      mybot.sendMessage(msg.sender.id, String(humidity) + "%");
    }
    if (msg.text.equalsIgnoreCase("temperatura bmp")) {
      Serial.print("Temperatura BMP");
      mybot.sendMessage(msg.sender.id, String(temperatureBMP) + "°C");
    }
    if (msg.text.equalsIgnoreCase("altitud")) {
      Serial.print("Altitud");
      mybot.sendMessage(msg.sender.id, String(altitude) + "m");
    }
    if (msg.text.equalsIgnoreCase("presion")) {
      Serial.print("Presion");
      mybot.sendMessage(msg.sender.id, String(pressure) + " hPa");
    }
    if (msg.text.equalsIgnoreCase("suelo")) {
      Serial.print("Suelo");
      mybot.sendMessage(msg.sender.id, String(sueloLectura));
    }
    if (msg.text.equalsIgnoreCase("temperatura agua")) {
      Serial.print("Temperatura DS18B20");
      mybot.sendMessage(msg.sender.id, String(temperatureDs18b20) + "°C");
    }
    if (msg.text.equalsIgnoreCase("datos")) {
      Serial.print("Todos los datos");
      Serial.print(msg.sender.id);
      mybot.sendMessage(msg.sender.id, String(Data));
    }
    if (msg.text.equalsIgnoreCase("guardar")) {
      Serial.print("Guardado");
      mybot.sendMessage(msg.sender.id, "Datos guardados");
      handleSave();
    }
    if (msg.text.equalsIgnoreCase("ayuda")) {
      Serial.print("Comandos");
      mybot.sendMessage(msg.sender.id, ayuda);
      handleSave();
    }
    if (msg.text.equalsIgnoreCase("encender")) {
      Serial.print("Luz");
      if (luzEncendida == true){
        mybot.sendMessage(msg.sender.id, "La luz ya esta encendida");
      } else {
        luzEncendida = true;
        mybot.sendMessage(msg.sender.id, "Se encendio la luz");
      }
    }
    if (msg.text.equalsIgnoreCase("apagar")) {
      Serial.print("Luz");
      if (luzEncendida == false){
        mybot.sendMessage(msg.sender.id, "La luz ya esta apagada");
      } else {
        luzEncendida = false;
        mybot.sendMessage(msg.sender.id, "Se apago la luz");
      }
    }
  }

  // ALERTAS POR TELEGRAM
  int test1 = 41;
  //Alertas de temperatura
  if (millis() - tiempo > 5000) {
    if (temperature > 40 || temperatureBMP > 40) {
      mybot.sendMessage(telegramId, "Temperatura elevada");
    }
    if (sueloLectura < 2500) {
      mybot.sendMessage(telegramId, "El suelo esta mojado");      
    }
    if (temperatureDs18b20 > 40) {
      mybot.sendMessage(telegramId, "Temperatura del agua elevada");
    }
    if (humidity > 90) {
      mybot.sendMessage(telegramId, "Humedad relativa elevada");
    }
    tiempo = millis();
  }


  server.handleClient();
  delay(500);

  Blynk.run();
  timer.run();
}
