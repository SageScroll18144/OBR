//MOTORES
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
 // digitalWrite(16,HIGH);
    /*if (Serial.available() > 0) {
     * 
        motors(Serial.read(),'F');
    }*/
  // desvio();
   // spinRobot('L');
   //forward();
//  OnOff();
  unsigned int sensor_1 = readAnLeft();
  //Serial.println(sensor_1);
  float normal_l = normalize(sensor_1);
  Serial.println(normal);
  
  //Serial.print(readAnRight());
  //Serial.print("\t");
  //Serial.println(readAnLeft());
  
  //desvio();
  //diagonal('L','F');
   /* Serial.print(readAnLeft());
    Serial.print("\t");*/
  //  Serial.println(readAnLeft());
    //Serial.println(ultrassonicRead(0));
}

float normalize(unsigned int data) {
  unsigned int MAX = (1<<10);

  float normalizado = (float)(MAX-data)/(float)MAX;

  return 1.0f - normalizado;
}

//======================FUNÇÕES DO MOVIMENTO DO ROBO==========================

//metodo de giro dos motores
void motors(int motor, char sen){//1o -> motor 0; 2o -> motor1; 3o -> motor 2; 4o -> motor 3
    if(sen == 'F'){
        digitalWrite(dir[motor*2], HIGH);
        digitalWrite(dir[(motor*2)+1], LOW);  
    }
    else if(sen == 'B'){
        digitalWrite(dir[motor*2], LOW);
        digitalWrite(dir[(motor*2)+1], HIGH);
    }
}
void stopRobot(int motor){
    digitalWrite(dir[motor*2], LOW);
    digitalWrite(dir[(motor*2)+1], LOW);  
}
//faz o robo seguir em frente
void forward(){
    for(int i = 0; i < 4; i++){
        motors(i, 'F');
    }
}
//faz o robo seguir na diagonal informada
void diagonal(char sen, char SenMotors){
  if(sen == 'R'){
    stopRobot(1);stopRobot(3);
    motors(0,SenMotors);motors(2,SenMotors);
  }
  else  if(sen=='L'){
    stopRobot(0);stopRobot(2);
    motors(1,SenMotors);motors(3,SenMotors);
  }
}
//faz o robo gira para a esquerda ou para a direita
void spinRobot(char sen){
    if(sen == 'L'){
        for(int i = 0; i < 2; i++){
            motors(i, 'B');
        }
        for(int i = 2; i < 4; i++){
            motors(i, 'F');
        }
    }
    else if (sen == 'R')
    {
        for(int i = 0; i < 2; i++){
            motors(i, 'F');
        }
        for(int i = 2; i < 4; i++){
            motors(i, 'B');
        }
    }
        
}
//======================FUNÇÕES DOS SENSORES ANALOG==========================
int readAnLeft(){
  return analogRead(A1);
}                           // ACIMA DE 600 É PRETO(const RB)
int readAnRight(){
  return analogRead(A15);
}/*
int readCornerLeft(){
  return analogRead(A2);//MODIFICAR
}
int readCornerRight(){
  return analogRead(A3);//MODIFICAR
}*/
//=======================FUNÇÃO DO ULTRASSONICO===============================
int ultrassonicRead(int sensor){//Retorna um valor inteiro com o valor da distância lida pelo ultrassônico
  long duracao;
  long distancia;
  digitalWrite(ultPin[0+sensor], LOW);
  delayMicroseconds(2);
  digitalWrite(ultPin[0+sensor], HIGH);
  delayMicroseconds(10);
  digitalWrite(ultPin[0+sensor], LOW);
  duracao = pulseIn(ultPin[2+sensor], HIGH);
  distancia = duracao/58;
  
  return distancia;
}

//===========================FUNÇÕES DOs RGBs=================================
void colorLeft()
{
  //Rotina que le o valor das cores
  digitalWrite(rgbs[2], LOW);
  digitalWrite(rgbs[3], LOW);
  //count OUT, pRed, RED
  red = pulseIn(rgbs[4], digitalRead(rgbs[4]) == HIGH ? LOW : HIGH);
  digitalWrite(rgbs[3], HIGH);
  //count OUT, pBLUE, BLUE
  blue = pulseIn(rgbs[4], digitalRead(rgbs[4]) == HIGH ? LOW : HIGH);
  digitalWrite(rgbs[2], HIGH);
  //count OUT, pGreen, GREEN
  green = pulseIn(rgbs[4], digitalRead(rgbs[4]) == HIGH ? LOW : HIGH);
}
int readRGBLeft(){
  colorLeft();
  if(green > 20 && red > 20 && blue > 20){//Verifica se a cor preta foi detectada
    return 0;//Preto
  }
  else if (green >= red && green >= blue)//Verifica se a cor branca foi detectada
  {
    return 1;//"Branco"
  }
  else if (green < red && green < blue)//Verifica se a cor verde foi detectada
  {
    return 2;//"Verde"
  }
}

void colorRight()
{
  //Rotina que le o valor das cores
  digitalWrite(rgbs[7], LOW);
  digitalWrite(rgbs[8], LOW);
  //count OUT, pRed, RED
  red1 = pulseIn(rgbs[9], digitalRead(rgbs[9]) == HIGH ? LOW : HIGH);
  digitalWrite(rgbs[8], HIGH);
  //count OUT, pBLUE, BLUE
  blue1 = pulseIn(rgbs[9], digitalRead(rgbs[9]) == HIGH ? LOW : HIGH);
  digitalWrite(rgbs[7], HIGH);
  //count OUT, pGreen, GREEN
  green1 = pulseIn(rgbs[9], digitalRead(rgbs[9]) == HIGH ? LOW : HIGH);
}
int readRGBRight(){
  colorRight();
  if(green1 > 20 && red1 > 20 && blue1 > 20){//Verifica se a cor preta foi detectada
    return 0;//PRETO
  }
  else if (green1 >= red1 && green1 >= blue1)//Verifica se a cor branca foi detectada
  {
    return 1;//BRANCO
  }
  else if (green1 < red1 && green1 < blue1)//Verifica se a cor verde foi detectada
  {
    return 2;//VERDE
  }
  
}
// =======================================================================================
//situações
/*void line(){
  if(readRGBLeft() == 2 && readRGBRight() == 2 && readAnLeft() <= RB && readAnRight() <= RB){
    // gira 180º 
  }
  else if(readRGBRight() == 2 && readAnRight() <= RB){
    //gira para a direita de maneira um pouco mais brusca
  }
  else if(readRGBLeft() == 2 && readAnLeft() <= RB){
    //gira para a esquerda de maneira um pouco mais brusca
  }
  else if(((readRGBRight() == 0 && readRGBLeft() == 1) || (readAnRight() >= RB && readAnLeft() <= RB)) && readCornerRight() <= 600){//caso for testar sem os sensores do canto, tirar a última condição
    // gira para a direita de maneira mais leve
  }
  else if(((readRGBLeft() == 0 && readRGBRight() == 1) || (readAnLeft() >= RB && readAnRight() <= RB)) && readCornerLeft() <= 600){//caso for testar sem os sensores do canto, tirar a última condição
    // gira para a esquerda de maneira mais leve
  }
  else{
    forward();//anda para frente
  }
}*/
void OnOff(){
  if(readAnRight() > 900 && readAnLeft() < 900){
    spinRobot('R'); 
  }
  else if(readAnRight() < 800 && readAnLeft() > 900){
    spinRobot('L'); 
  }
  else{
    forward();
  }
}
void desvio(){
  if(ultrassonicRead(0) < 7){
    diagonal('L','F');
    delay(1300);
    forward();
    delay(1000);
    diagonal('R','F');
    delay(700);
    stopRobot(0);stopRobot(1);stopRobot(2);stopRobot(3);
    delay(500);
  }
  else{
    forward();
  }
}
