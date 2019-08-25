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
void backward(){
  for(int i = 0; i < 4; i++){
      motors(i, 'B');
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
void giro_de_noventa_green(char sen){
  forward();
  delay(300);
  spinRobot(sen);
  delay(750);
  for(int i = 0;i<4; i++){
    stopRobot(i);
  }
}
void spinSuave(char sen){
  if(sen ==  'R'){
     motors(0, 'F'); 
     motors(1, 'F'); 
     stopRobot(2);
     stopRobot(3);
  }else if(sen == 'L'){
     motors(3, 'F'); 
     motors(2, 'F'); 
     stopRobot(1);
     stopRobot(0);
  }
}
void go_right(){
  for(int i = 0; i < 4; i++){
    if((i%2) == 0){
      motors(i, 'B');
    }
    else{
      motors(i, 'F');
    }
  }
}
void go_left(){
  for(int i = 0; i < 4; i++){
    if((i%2) == 0){
      motors(i, 'F');
    }
    else{
      motors(i, 'B');
    }
  }
}
