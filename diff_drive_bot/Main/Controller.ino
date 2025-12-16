void PIDcal (struct PID *pid)
{
  int PV;
  long Error;
  long Pterm, Dterm, Iterm, PIDOutput;

  PV = (pid->Encoder) - (pid->PrevEnc);
  Error = pid->Setpoint - PV;
  // Serial.println(Error);

  Pterm  = Kp * Error;
  Dterm  = Kd * ( PV - (pid->PrevPV) ); 
  Iterm  = Ki * (pid->Iterm);

  PIDOutput = (Pterm + Iterm - Dterm) / (Ko);
  PIDOutput += (pid->output);
  pid->PrevEnc = pid->Encoder;

  if (PIDOutput > PWM_MAX) 
    PIDOutput = PWM_MAX;
  else if (PIDOutput < -PWM_MAX) 
    PIDOutput = -PWM_MAX;
  else  
    pid->Iterm += Error;

  pid->output = PIDOutput;
  pid->PrevPV = PV;
}


void resetPID()  
{
  LeftPID.Setpoint = 0;
  LeftPID.Encoder = readEncoder(LEFT);
  LeftPID.PrevEnc = LeftPID.Encoder;
  LeftPID.output = 0;
  LeftPID.PrevPV = 0;
  LeftPID.Iterm = 0;

  RightPID.Setpoint = 0;
  RightPID.Encoder = readEncoder(RIGHT);
  RightPID.PrevEnc = RightPID.Encoder;
  RightPID.output = 0;
  RightPID.PrevPV = 0;
  RightPID.Iterm = 0;
}


void runPID()  
{
  LeftPID.Encoder = readEncoder(LEFT);
  RightPID.Encoder = readEncoder(RIGHT);

  if (!moving){
    if (LeftPID.PrevPV != 0 || RightPID.PrevPV != 0) resetPID();
    return;
  }

  PIDcal (&LeftPID);
  PIDcal (&RightPID);

  motor1_ctrl(LeftPID.output);
  motor2_ctrl(RightPID.output);
}
