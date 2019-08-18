void PID(float limite){
  pid_update(readAnLeft(), readAnRight());
  float x = pid_actuation(1.0, 1.0, 1.0);
  if(abs(x > limite)){
    if(x < 0){
      spinRobot('L');
    }else{
      spinRobot('R');
    }
  }
  else{
    forward();
  }
}

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
  diagonal('L','F');
  delay(1500);

  forward();
  delay(1000);  
   diagonal('R','F');
  delay(1100);
  for(int i = 0; i < 4; i++){
      stopRobot(i);
  }
  delay(1000);
}

void desvio_teste(){
  stopRobot(0);stopRobot(1);stopRobot(2);stopRobot(3);
  delay(50);
  diagonal('L','F');
  delay(1000);
  while(1){
    if(ultrassonicRead(1) < 10){
      forward();
    }
    else if(ultrassonicRead(1) > 10){
        diagonal('R','F');
        if( readRGBRight()==0){break;}
    }
  }
  stopRobot(0);stopRobot(1);stopRobot(2);stopRobot(3);
  delay(500);
}
void resgate(int dimensao){
  if(ultrassonicRead(1) > dimensao - 5 && ultrassonicRead(0) < 3){
    area_de_resgate();
  }

  else if (ultrassonicRead(1) < dimensao) {
    spinRobot('R');
    delay(850);
    while(ultrassonicRead(0) > 5){
      forward();
    }
    get_the_ball();
    spinRobot('L');
    delay(1500);
    while(ultrassonicRead(0) > 5){
      forward();
    }
    spinRobot('R');
    delay(850);
  }
  
  else{
    forward();
  }

}
void get_the_ball(){

  //captura
  
}
void area_de_resgate(){

  //procura e joga as vitimas na area de resgate
}
