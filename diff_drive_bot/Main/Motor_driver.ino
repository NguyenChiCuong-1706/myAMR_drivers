void motor1_ctrl(int pwm)
{
  int8_t dir=1;

  if(pwm < 0) {
    dir=-1;
    pwm = pwm * (-1);
  }

  if (pwm > PWM_MAX) pwm = PWM_MAX;
  digitalWrite(PWML1_M1,LOW);
  digitalWrite(PWML2_M1,LOW);
  if(dir==1){
    digitalWrite(PWML1_M1,HIGH);
    digitalWrite(PWML2_M1,LOW);
    analogWrite(EN_M1,pwm);
  }
  else {
    digitalWrite(PWML1_M1,LOW);
    digitalWrite(PWML2_M1,HIGH);
    analogWrite(EN_M1,pwm);
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
  digitalWrite(PWML1_M2,LOW);
  digitalWrite(PWML2_M2,LOW);
  if(dir==1){
    digitalWrite(PWML1_M2,HIGH);
    digitalWrite(PWML2_M2,LOW);
    analogWrite(EN_M2,pwm);
  }
  else {
    digitalWrite(PWML1_M2,LOW);
    digitalWrite(PWML2_M2,HIGH);
    analogWrite(EN_M2,pwm);
  }
}