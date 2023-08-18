//definimos los pines de nuestros botones

int btn1 = 4;
int btn2 = 5;
int btn3 = 6;
int btn4 = 7;
int btn5 = 8;
int btn6 = 9;

//inicilizamos variables para los botones 1 o 0
int var1;
int var2;
int var3;
int var4;
int var5;
int var6;

//inicilizamos variables para nuestros switches
int interruptor1;
int interruptor2;

//definimos pin para motor DC
int motorDCp = 9;
int motorDCn = 10;

//definimos pin para motor DC
int motorAC = 8;

bool motorEncendido;
bool motorEncendidoAC;


unsigned long msegi = 0;


void setup() {
  Serial.begin(9600);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
  pinMode(btn5, INPUT);
  pinMode(btn6, INPUT);

  pinMode(motorDCp, OUTPUT);
  pinMode(motorDCn, OUTPUT);

  pinMode(motorAC, OUTPUT);
}

void loop() {
  var1 = digitalRead(btn1);
  var2 = digitalRead(btn2);
  var3 = digitalRead(btn3);
  var4 = digitalRead(btn4);
  var5 = digitalRead(btn5);
  var6 = digitalRead(btn6);

  unsigned long msegf = millis();


  if (motorEncendido == true){
    digitalWrite(motorDCp, HIGH);
    digitalWrite(motorDCn, LOW);
  }

  if (motorEncendido == false){
    digitalWrite(motorDCp, LOW);
    digitalWrite(motorDCn, LOW);
  }

  if (motorEncendidoAC == true){
    digitalWrite(motorAC, HIGH);
  }

  if (motorEncendidoAC == false){
    digitalWrite(motorAC, LOW);
  }

  if (msegf-msegi >= 100){
    msegi=msegf;
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
    Serial.println(var6);
  }
}

void serialEvent(){
  if(Serial.available()){
    interruptor1=Serial.parseInt();
    interruptor2=Serial.parseInt();
    if(interruptor1 == 1){
      motorEncendido = true;
    }
    if(interruptor1 == 0){
      motorEncendido = false;
    }
    if(interruptor2 == 1){
      motorEncendidoAC = true;
    }
    if(interruptor2 == 0){
      motorEncendidoAC = false;
    }
  }
}
