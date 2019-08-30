void PID(int esquerda, int direita){
 pid_update(analogRead(irs[2]), analogRead(irs[5]));
 float x = pid_actuation(3.0, 5.0, 2.0);
 Serial.println(x);
 if(readRGBRight() == 2 && readRGBLeft() == 2){
  retorno();
 }
 else if(readRGBLeft() == 2 && digitalRead(irs[3]) == 1){
  giro_de_noventa_green('L');
 }
 else if(readRGBRight() == 2 && digitalRead(irs[3]) == 1){
  giro_de_noventa_green('R');
 }
 if(digitalRead(irs[0]) == 1 || digitalRead(irs[7]) == 1 && digitalRead(IR_F) == 1){
  forward();
 }
 if(x < esquerda){
   spinRobot('L');
 }
 else if(x > direita){
   spinRobot('R');
 }
 else {
   forward();
 }
 
}

void PIDD(float esquerda, float direita, float en, float ed){
 pid_update(analogRead(irs[2]), analogRead(irs[5]));
 float x = pid_actuation(3.0, 5.0, 2.0);
 Serial.println(x);
 
 if(readRGBRight() == 2 && readRGBLeft() == 2){
  retorno();
 }
 else if(readRGBLeft() == 2 && digitalRead(irs[3]) == 1){
  giro_de_noventa_green('L');
 }
 else if(readRGBRight() == 2 && digitalRead(irs[3]) == 1){
  giro_de_noventa_green('R');
 }
 
 if(digitalRead(irs[0]) == 1 || digitalRead(irs[7]) == 1 && digitalRead(IR_F) == 1){
  forward();
 }
 else if(digitalRead(irs[0]) == 1 && digitalRead(irs[1]) == 1 && digitalRead(irs[2]) == 1 && digitalRead(irs[6]) == 0 && digitalRead(irs[7]) == 0){
  ninety('L');
 }
 else if(digitalRead(irs[0]) == 0 && digitalRead(irs[1]) == 0 && digitalRead(irs[2]) == 0 && digitalRead(irs[6]) == 1 && digitalRead(irs[7]) == 1){
  ninety('R');
 }
 
 if(x <= en){
   spinRobot('L');
 }
 else if(x>=ed){
   spinRobot('R');
   
 }
 else if(x < esquerda){
   spinSuave('L');
 }
 else if(x > direita){
   spinSuave('R');
 }
 else {
   forward();
 
 }
 
}
void PID_VEL(float direita, float esquerda, float ideal){
 pid_update(analogRead(irs[2]), analogRead(irs[5]));
 float x = pid_actuation(3.0, 5.0, 2.0);
 if(readRGBRight() == 2 && readRGBLeft() == 2){
  retorno();
 }
 else if(readRGBRight() == 2){
  spinSuave('R');
 }
 else if(readRGBLeft() == 2){
  spinSuave('L');
 }
 else if(x < esquerda){
   spinRobot('L');
 }
 else if(x > direita){
   spinRobot('R');
 }
  else{
    for(int i = 0; i < 4; i++){
      if(i > 1){
        set_velocity(i, (512*ideal/x));
      }else{
        set_velocity(i, (512*x/ideal));
      }
    }
    forward();
  }
}

void OnOff(){
  if(readRGBRight() == 0){
    spinRobot('R'); 
  }
  else if(readRGBLeft() == 0){
    spinRobot('L'); 
  }
  else{
    forward();
  }
}

void desvio(){
  go_left();
  delay(1000);
  forward();
  delay(2300);
  go_right();
  delay(1000);
  for(int i = 0;i<4; i++){
    stopRobot(i);
  }
  delay(1000);
}

void desvio_diagonal(){
  int ant = 0;
  
  diagonal('L','F');
  delay(1500);
  while(1){
    if(ultrassonicRead(1) < 15){
      ant++;
      break;
    }
    else{
      forward();
    }
  }
  while(1){
    if(ultrassonicRead(1) > 15){
      break;
    }
    else{
      forward();
    }
  }
  diagonal('R','F');
  delay(1500);
  
  for(int i = 0; i < 4; i++){
      stopRobot(i);
  }
  delay(1000);
}
