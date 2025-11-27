void motor1_ctrl(int pwm)
{
  int8_t dir=1;

  if(pwm < 0) {
    dir=-1;
    pwm = pwm * (-1);
  }

  if (pwm > PWM_MAX) pwm = PWM_MAX;

  if(dir==1){
    digitalWrite(EN_M1,0);
    analogWrite(PWML1_M1,pwm);
    analogWrite(PWML2_M1,1);
  }
  else {
    digitalWrite(EN_M1,0);
    analogWrite(PWML1_M1,1);
    analogWrite(PWML2_M1,pwm);
  }
}

void motor2_ctrl(int pwm)
{
  int8_t dir=1;

  if(pwm < 0) {
    dir=-1;
    pwm = pwm * (-1);
  }

  if (pwm > PWM_MAX) pwm = PWM_MAX;

  if(dir==1){
    digitalWrite(EN_M2,0);
    analogWrite(PWML1_M2,pwm);
    analogWrite(PWML2_M2,1);
  }
  else {
    digitalWrite(EN_M2,0);
    analogWrite(PWML1_M2,1);
    analogWrite(PWML2_M2,pwm);
  }
}