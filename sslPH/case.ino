#define V_MAX 255

void PID(){
  pid_update(readAnLeft(), readAnRight());
  float controle = pid_actuation(1.0, 1.0, 1.0);
  //faltar continuar ksksks
}


void OnOff(){
  for(int i = 0; i < sizeof(vel)/sizeof(int); i++){
    set_velocity(i, V_MAX);
  }
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
  for(int i = 0; i < sizeof(vel)/sizeof(int); i++){
    set_velocity(i, V_MAX);
  }
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
