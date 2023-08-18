#include <Key.h>
#include <Keypad.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <TimerOne.h>
//*** TECLADO
const byte fil=4;
const byte col=4;
char keys[fil][col]={
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'},
};
byte pinFil[fil]={9,8,7,6};
byte pinCol[col]={5,4,3,2};
Keypad teclado= Keypad(makeKeymap(keys),pinFil,pinCol,fil,col);
//*** MOTOR STEPPER
AccelStepper motor(4,13,11,12,10);
//******* variables del timer
volatile long int tiempo=0;
//******variables globales
bool flag = false;
char tecla;
String valor;
//*******VARIABLES DE CONTROL PROGRAMA
int grados=0;
int stop=0;
int sentido=0;
void setup() {
 // put your setup code here, to run once:
 Serial.begin(9600);
 motor.setSpeed(800);
 motor.setAcceleration(50);
 motor.setMaxSpeed(1000);
 Timer1.initialize(1000000);
 Serial.println("MENU");
 Serial.println("A: GRADOS");
 Serial.println("B: TIEMPO");
 Serial.println("C: SENTIDO");
 
 }
void loop() {
  // put your main code here, to run repeatedly:
  capturarTecla();
  if (grados!=0 && stop!=0 && sentido != 0) {
    //Serial.println("FUNCIONA");
    if (flag==false) {
      Timer1.attachInterrupt(regularTiempo);
      flag=true;
    }
    if (motor.distanceToGo()==0) {
      motor.move(grados*sentido);
    }
  }
  motor.run();
}
void regularTiempo(void)
{
  //***VERIFICANDO VAR GLOBALES
  /*Serial.println(grados);
  Serial.println(stop);
  Serial.println(sentido);*/
  Serial.println("----------");
  //******
  tiempo++;
  Serial.println(tiempo);
  if (tiempo>=stop) {
    flag=false;
    tiempo=0;
    grados=0;
    stop=0;
    sentido=0;
    Timer1.detachInterrupt();
  }
}
void capturarTecla()
{
  tecla=teclado.getKey();
  if (tecla!=NO_KEY) {
  valor=valor+tecla;
  switch (tecla) {
  case 'A':
  Serial.println("Ingrese los grados: ");
  Serial.println("----------");
  opcionA();
  Serial.println(grados);
  //***op a
  break;
  case 'B':
  Serial.println("Ingrese el tiempo: ");
  opcionB();
  Serial.println(stop);
  //*** op b
  break;
  case 'C':
  Serial.println("Ingrese el sentido: ");
  opcionC();
  Serial.println(sentido);
  //** op c
  break;
  default:
  break;
  } 
  }
}
void opcionA()
{
  grados =valor.toInt();
  valor="";
}
void opcionB()
{
  stop =valor.toInt();
  valor="";
}
void opcionC()
{
  if (valor.toInt()==1) { //HORARIO
  sentido=1;
  }
  else if(valor.toInt()==2)
  {
  sentido=-1;
  }
  valor="";
}
