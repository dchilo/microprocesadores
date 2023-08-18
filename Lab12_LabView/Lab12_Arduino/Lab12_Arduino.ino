//configuramos los pines que seran nuestros switches
int btn1 = 8;
int btn2 = 9;

//inicializamos las variables para guardar los valores de los switches
int var1;
int var2;

unsigned long msegi = 0;


void setup() {
  Serial.begin(9600);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);

}


void loop() {
  //leemos los valores y los guardamos en sus respectivas variables
  var1 = digitalRead(btn1);
  var2 = digitalRead(btn2);

  //miramos cuanto tiempo ha pasado desde que se ejecuto el programa
  unsigned long msegf = millis();
  
  if (msegf-msegi >= 100){
    msegi = msegf;
    //mandamos los datos leidos a labview
    Serial.print(var1);
    Serial.print(',');
    Serial.println(var2);
  }
}
