void PID(){
 pid_update(readAnLeft(), readAnRight());
 float x = pid_actuation(3.0, 5.0, 2.0);
 if(x < 3.90){
   spinRobot('L');
 }
 else if(x > 5.55){
   spinRobot('R');
 }
 else if(3.90 < x < 5.55){
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
void resgate(int dimensaoX, int dimensaoY){
  while(1){
    go_right();
    if(ultrassonicRead(0) <= dimensaoY - 5){
      get_the_ball();
    }
    else if(ultrassonicRead(1) >= dimensaoX - 5){
      break;
    } 
  }

}
void get_the_ball(){

  forward();
  if(ultrassonicRead(0) < 10){
    for(int i = 0; i < 4; i++){
      stopRobot(i);
    }
    //captura
    backward();
  }  
}
void area_de_resgate(){
  //procura e joga as vitimas na area de resgate
}
