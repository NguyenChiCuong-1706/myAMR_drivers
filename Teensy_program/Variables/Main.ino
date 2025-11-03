#define LEFT_RPM_CMD 100
#define RIGHT_RPM_CMD 100
int LEFT_desireSPD=0;
int RIGHT_desireSPD=0;

// Increase PWM resolution to 16bit
void loop()
{
  struct PID LeftPID;
  struct PID RightPID;

  long Lpulse = readPulse_LEFT();
  long Rpulse = readPulse_RIGHT();
  float Lspeed = readSpeed_LEFT(Lpulse);
  float Rspeed = readSpeed_RIGHT(Rpulse);

  receive();
  RF_read(&LEFT_desireSPD,&RIGHT_desireSPD);
  
  resetPID(&LeftPID, &RightPID, Lspeed, Rspeed);
  PIDcal (&LeftPID, LEFT_RPM_CMD, Lspeed);
  PIDcal (&RightPID, RIGHT_RPM_CMD, Rspeed);
  
  motor1_ctrl(LeftPID.output);
  motor2_ctrl(RightPID.output);
}
