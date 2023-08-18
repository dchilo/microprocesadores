//inicializamos las variables para guardar los valores de los potenciometros
int var1;
int var2;
int var3;
int var4;
int var5;
int var6;
int var7;
int var8;

unsigned long msegi = 0;


void setup() {
  //inicializamos el Serial
  Serial.begin(9600);
  //ponemos los pines como entradas para los potenciometros
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
}

void loop() {
  //leemos los valores y los guardamos en sus respectivas variables
  var1 = analogRead(A0);
  var2 = analogRead(A1);
  var3 = analogRead(A2);
  var4 = analogRead(A3);
  var5 = analogRead(A4);
  var6 = analogRead(A5);
  var7 = analogRead(5);
  var8 = analogRead(6);

  //miramos cuanto tiempo ha pasado desde que se ejecuto el programa
  unsigned long msegf = millis();
  
  if (msegf-msegi >= 100){
    msegi = msegf;
    //mandamos los datos leidos a labview
    Serial.print(var1);
    Serial.print(',');
    Serial.print(var2);
    Serial.print(',');
    Serial.print(var3);
    Serial.print(',');
    Serial.print(var4);
    Serial.print(',');
    Serial.print(var5);
    Serial.print(',');
    Serial.print(var6);
    Serial.print(',');
    Serial.print(var7);
    Serial.print(',');
    Serial.println(var8);
  }
}