// Quantos ciclos de erro vamos guardar
#define ERROR_LENGTH 20

// Uma queue, menor o index, mais recente
float ERRO[ERROR_LENGTH];

void pid_update(unsigned int raw_left, unsigned int raw_right) {
  float norm_left = pid_normalize(raw_left);
  float norm_right = pid_normalize(raw_right);

  float erro = 0;

  erro -= norm_left;
  erro += norm_right;

  pid_push(erro);

}

void pid_push(float val) {
  // TODO: talvez isso aqui não funcione
  for(unsigned int i = (ERROR_LENGTH-1); i > 0; i--) {
    ERRO[i] = ERRO[i-1];
  }

  ERRO[0] = val;
}

// P_W, peso da proporcio, D_W, peso da derivada, I_W peso da integral.
float pid_actuation(float p_w, float d_w, float i_w) {
  return (p_w * pid_prop()) + (d_w * pid_derivada()) + (i_w * pid_integral());
}

// Erro proporcional básico do pid
float pid_prop() {
  return ERRO[0];
}

// Derivada dp pid, equivalente a velocidade em que a linha se move.
float pid_derivada() {
  if(ERRO[1] == 0.0f) return ERRO[0];
  return ERRO[0]/ERRO[1];
}

// Integral do pid, equivalente ao erro acumulado em ERROR_LENGTH ciclos.
float pid_integral() {

  float erro_ac = 0.0f;

  for(unsigned int i = 0; i < ERROR_LENGTH; i++) {
    erro_ac += ERRO[i];
  }

  return erro_ac/ (float)ERROR_LENGTH;
}

float pid_normalize(unsigned int data) {
  unsigned int MAX = (1<<10);

  float normalizado = (float)(MAX-data)/(float)MAX;

  return 1.0f - normalizado;
}
float err(){
  return ERRO[0];
}
