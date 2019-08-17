//======================FUNÇÕES DOS SENSORES ANALOG==========================
int readAnLeft(){
  return analogRead(A1);
}                           // ACIMA DE 600 É PRETO(const RB)
int readAnRight(){
  return analogRead(A15);
}
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
  if ((green + red + blue) < 45 && (green + red + blue)> 25)//Verifica se a cor verde foi detectada
  {
    return 2;//VERDE
  }
  else if((green + red + blue) > 75){//Verifica se a cor preta foi detectada
    return 0;//PRETO
  }
  else if ((green + red + blue) < 25 )//Verifica se a cor branca foi detectada
  {
    return 1;//BRANCO
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
  if ((green1 + red1 + blue1) < 45 && (green1 + red1 + blue1 )> 25)//Verifica se a cor verde foi detectada
  {
    return 2;//VERDE
  }
  else if((green1 + red1 + blue1) > 75){//Verifica se a cor preta foi detectada
    return 0;//PRETO
  }
  else if ((green1 + red1 + blue1) < 25 )//Verifica se a cor branca foi detectada
  {
    return 1;//BRANCO
  }
  
}
