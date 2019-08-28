#include "SparkFun_MMA8452Q.h"

#include <SPI.h>              
#include <BnrOneA.h>
#include <EEPROM.h>    

//Constants definitions
//Definir constantes
#define SSPIN  2    //SPI communication
#define M1  1       //Motor1
#define M2  2       //Motor2
BnrOneA one;  

//ULTRASSONICO
//int trig = 5;
//int echo = 6;
int ultPin[] = {5,34,0,6,36,0};//trig;trig;trig;echo;echo;echo

//RGB
//s0; s1; s2; s3; out -> Pino digital || gnd -> gnd || vcc -> 5v
const int rgbs[] = {2,3,26,24,28,8,9,11,12,10}; //s0 s1 s2 s3 out 

int red = 0;
int green = 0;
int blue = 0;

int red1 = 0;
int green1 = 0;
int blue1 = 0;

int matriz_analog[8];
/*
 M0  ####  M3
    ######       -> chassi do robô
    ######       -> M(motor)[número do motor]
 M1  ####  M2
*/
//CONSTANTES
#define RB 600 // Valor lido pelo sensor analógico

MMA8452Q accel;  

void setup(){
  one.spiConnect(SSPIN);   // start the SPI module
  one.stop();   
  
  Serial.begin(9600);
 
  for(int i = 0; i < sizeof(ultPin)/sizeof(int); i++){
    if (i > 2)
      pinMode(ultPin[i], INPUT);
    else
      pinMode(ultPin[i], OUTPUT);
  }
  accel.init();
  acl_init();

}

void loop(){
  for(int i = 0; i < sizeof(matriz_analog)/sizeof(int); i++){
    matriz_analog[i] = one.readAdc(i);
  }
  
  pid_update(matriz_analog[2], matriz_analog[5]);
  float x = pid_actuation(3.0, 5.0, 2.0);
  Serial.println(x);
}
