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
  stopRobot(0);stopRobot(1);stopRobot(2);stopRobot(3);
  delay(50);
  diagonal('L','F');
  delay(1000);
  while(1){
    //ultrassonico que está posicionado a direita em relação a frente do robô
    if(ultrassonicRead(1) < 15){
      forward();
    }
    else if(ultrassonicRead(1) > 15){
        diagonal('R','F');
        if(readAnRight() > 900){break;}
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
