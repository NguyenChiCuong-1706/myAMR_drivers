#ifdef MOTOR
  #define EN_M1 38
  #define PWML1_M1 12
  #define PWML2_M1 24

  #define EN_M2 6
  #define PWML1_M2 7
  #define PWML2_M2 8
#endif

void motor1_ctrl(int pwm);
void motor2_ctrl(int pwm);
