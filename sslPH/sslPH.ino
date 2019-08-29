#include "SparkFun_MMA8452Q.h"

//MOTORES
const int dir[] = {51,53,45,43,41,39,47,49};//pinos de direção dos motores

//ULTRASSONICO
//int trig = 5;
//int echo = 6;
const int ultPin[] = {5,34,0,6,36,0};//trig;trig;trig;echo;echo;echo

//RGB
//s0; s1; s2; s3; out -> Pino digital || gnd -> gnd || vcc -> 5v
const int rgbs[] = {2,3,26,24,28,8,9,11,12,10}; //s0 s1 s2 s3 out 

const int irs[] = {A8,A9,A10,A11,A12,A13,A14,A15};

int red = 0;
int green = 0;
int blue = 0;

int red1 = 0;
int green1 = 0;
int blue1 = 0;
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
  for(int i = 0; i < sizeof(dir)/sizeof(int); i++){
      pinMode(dir[i], OUTPUT);
  }
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
 PID(0,0);
}
