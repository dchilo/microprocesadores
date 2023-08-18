int led1 = 13;
int led2 = 12;
int led3 = 14;
int led4 = 27;
int led5 = 26;
int led6 = 25;
int led7 = 33;
int led8 = 32;

int ledPins[] = {led1, led2, led3, led4, led5, led6, led7, led8};

int pulsador1 = 22;
int pulsador2 = 23;

int lectura1 = 0;
int lectura2 = 0;

void setup(){

  Serial.begin(115200);
  pinMode(pulsador1, INPUT_PULLUP);
  pinMode(pulsador2, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
}

void loop(){
  lectura1 = digitalRead(pulsador1);
  lectura2 = digitalRead(pulsador2);

  Serial.println(lectura1);
  Serial.println(lectura2);

  if(lectura1 == 0 && lectura2 == 1){
    for(int i = 0; i<8; i++){
      digitalWrite(ledPins[i], 1);
      delay(100);
      digitalWrite(ledPins[i], 0);
    }
  }
  if(lectura1 == 1 && lectura2 == 0){
    for(int i = 8; i>0; i--){
      digitalWrite(ledPins[i], 1);
      delay(100);
      digitalWrite(ledPins[i], 0);
    }
  }
  if(lectura1 ==  lectura2){
    digitalWrite(led1, 0);
    digitalWrite(led2, 0);
    digitalWrite(led3, 0);
    digitalWrite(led4, 0);
    digitalWrite(led5, 0);
    digitalWrite(led6, 0);
    digitalWrite(led1, 0);
    digitalWrite(led1, 0);
  }

}