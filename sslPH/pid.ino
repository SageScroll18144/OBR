float normalize(unsigned int data) {
  unsigned int MAX = (1<<10);

  float normalizado = (float)(MAX-data)/(float)MAX;

  return 1.0f - normalizado;
}
