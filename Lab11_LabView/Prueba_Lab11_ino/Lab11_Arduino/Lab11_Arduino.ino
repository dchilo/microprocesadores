
// inicializamos las variables de los switches
int var1;
int var2;


void setup() {
  Serial.begin(9600);
  //ponemos los pines de los 8 leds como salida
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

}

void loop() {
}

void serialEvent(){
    if(Serial.available()){
    //leemos los valores de los switches que pueden ser 1 o 0 (alto o bajo)
    var1=Serial.parseInt();
    var2=Serial.parseInt();
    //leemos los datos recibidos
    if(Serial.read()==char(13)){
      //verificamos si el primero esta en alto y el segundo en bajo para realizar la rotacion que corresponde
      if(var1 == 1 && var2 == 0) {
        for (int i = 0; i <= 7; i++){
          digitalWrite(i, HIGH);
          delay(1000);
          digitalWrite(i, LOW);
          delay(1000);
        }
      }
      //verificamos si el primero esta en bajo y el segundo en alto para realizar la rotacion que corresponde
      if(var1 == 0 && var2 == 1) {
        for (int i = 7; i >= 0; i--){
          digitalWrite(i, HIGH);
          delay(1000);
          digitalWrite(i, LOW);
          delay(1000);
        }
      }
      //verificamos si ambos son iguales para no realizar rotacion
      if(var1 == var2) {
          digitalWrite(0, HIGH);
          digitalWrite(1, HIGH);
          digitalWrite(2, HIGH);
          digitalWrite(3, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(5, HIGH);
          digitalWrite(6, HIGH);
          digitalWrite(7, HIGH);
      }
    }
  }
}


