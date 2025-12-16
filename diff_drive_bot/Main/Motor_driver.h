#ifdef MOTOR
  #define EN_M1 15
  #define PWML1_M1 14
  #define PWML2_M1 13

  #define EN_M2 9
  #define PWML1_M2 8
  #define PWML2_M2 7
#endif

void motor1_ctrl(int pwm);
void motor2_ctrl(int pwm);
