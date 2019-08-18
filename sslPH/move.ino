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
void giro_de_noventa_green(char sen){
  forward();
  delay(300);
  spinRobot(sen);
  delay(750);
  for(int i = 0;i<4; i++){
    stopRobot(i);
  }
}
