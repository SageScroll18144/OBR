//MOTORES
int vel[] = {0,0,0,0};//pinos de velocidade dos motores(PWMs){m0,m1,m2,m3}
int dir[] = {51,53,45,43,41,39,47,49};//pinos de direção dos motores

//ULTRASSONICO
//int trig = 5;
//int echo = 6;
int ultPin[] = {5,0,6,0};//trig;trig;echo;echo

//RGB
//s0; s1; s2; s3; out -> Pino digital || gnd -> gnd || vcc -> 5v
const int rgbs[] = {2,3,26,24,28,8,9,11,12,10}; //s0 s1 s2 s3 out 

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
void setup(){
  for(int i = 0; i < sizeof(dir)/sizeof(int); i++){
      pinMode(dir[i], OUTPUT);
  }
  Serial.begin(9600);
 
  for(int i = 0; i < sizeof(ultPin)/sizeof(int); i++){
      if (i > 1)
        pinMode(ultPin[i], INPUT);
      else
        pinMode(ultPin[i], OUTPUT);
  }

}

void loop(){
  unsigned int sensor_1 = readAnLeft();
  float normal_l = pid_normalize(sensor_1);
  Serial.println(normal_l);
}
