void PID(float esquerda, float direita, float ideal){
  
  for(int i = 0; i < sizeof(matriz_analog)/sizeof(int); i++){
    matriz_analog[i] = one.readAdc(i);
  }
  
  pid_update(matriz_analog[2], matriz_analog[5]);
  float x = pid_actuation(3.0, 5.0, 2.0);

  move.one((50*retorno/ideal), (50*ideal/retorno));
  
  if(readRGBRight() == 2 && readRGBLeft() == 2){
   one.move(-50,50);//ENCODER
   delay(500);//TROCAR DEPOIS
  }
  else if(x > direita || readRGBRight() == 2){
    move.one(0,50);
  }
  else if(x < esquerda || readRGBLeft() == 2){
   move.one(50,0);
  }
 
}

void OnOff(){

}


void desvio(){
  
}
