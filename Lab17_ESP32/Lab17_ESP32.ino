int suelos = 33; //porque el begin esta habilitado, solo se usa los ADC1

void setup() {
  Serial.begin(115200);
}
void loop() {
  int lectura = analogRead(suelos);
  Serial.println(lectura);
  if (lectura < 2000){
    Serial.println("Esta mojado");
  }
  if (lectura >= 2000 && lectura <= 3000){
    Serial.println("Esta humedo");
  }
  if (lectura > 3000){
    Serial.println("Esta seco");
  }
  delay(5000);
}
