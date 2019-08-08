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