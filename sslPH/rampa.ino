#define STACK_LENGTH 10

int valuesAcl[STACK_LENGTH];

unsigned long long int tempo = 0;

void acl_update(){
  if(accel.available() && (millis() - tempo) >= 3000) {   
    if(accel.getCalculatedX() > 0){
      acl_push(1);
    }
    else{
      acl_push(0);
    }
    tempo = millis();
  }
}

void acl_push(int value){
  for(int i = STACK_LENGTH - 1; i > 0; --i){
    valuesAcl[i] = valuesAcl[i-1];
  }
  valuesAcl[0] = value;
}
boolean input_rescue(){
  boolean rtt = false;
  for(int i = STACK_LENGTH - 1; i >= 0; --i){
    if(i != 0 && valuesAcl[i] != 1){
      rtt = false;
      break;
    }
    else if(i == 0 && valuesAcl[i] == 0){
      rtt = true;
      break;
    }
  }
  return rtt;
}
void acl_init(){
  for(int i = 0; i < STACK_LENGTH; i++){
    valuesAcl[i] = 0;
  }
}
