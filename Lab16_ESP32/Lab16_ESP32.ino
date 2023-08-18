int verde = 26;
int rojo = 25;
int frecuencia = 5000; //kHz ->1-40000 kHz
int canal1 = 0; //0-15
int canal2 = 1;
int resolucion = 8; //0-255 -> 1 - 16 bits
void setup() {
 ledcSetup(canal1,frecuencia,resolucion); //configura el modo de trabajo del PWM
 ledcAttachPin(verde, canal1); //Agregar el canal al GPIO
 ledcAttachPin(rojo, canal2);
}
void loop() {
 for(int valor=0;valor<=255;valor++){
 ledcWrite(canal1,valor);
 delay(10);
 }
 for(int valor=254;valor>0;valor--){
 ledcWrite(canal1,valor);
 delay(10);
 }
for(int valor=0;valor<=255;valor++){
 ledcWrite(canal2,valor);
 delay(10);
 }
 for(int valor=254;valor>0;valor--){
 ledcWrite(canal2,valor);
 delay(10);
 }
}