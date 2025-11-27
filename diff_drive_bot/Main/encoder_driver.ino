long Pre_LEFT_PUL;
long Pre_RIGHT_PUL;
long ENC_LEFT_PUL=0;
long ENC_RIGHT_PUL=0;
float pul_per_loop=0;

unsigned long lastTime_LEFT=0,lastTime_RIGHT=0;

const int8_t QEM [16] = {0,-1,1,2,1,0,2,-1,-1,2,0,1,2,1,-1,0};

void leftEncoderISR() 
{
  NewL = digitalReadFast (ENC_LEFT_A) * 2 + digitalReadFast (ENC_LEFT_B); 
  uint8_t ix = OldL * 4 + NewL;
  OutL = QEM [ix];
  
  if (OutL==1) {ENC_LEFT_PUL --;}
  else if (OutL==-1) {ENC_LEFT_PUL ++;}
  OldL = NewL;
}


void rightEncoderISR() 
{
  OldR = NewR;
  NewR = digitalReadFast (ENC_RIGHT_A) * 2 + digitalReadFast (ENC_RIGHT_B); 
  OutR = QEM [OldR * 4 + NewR];
  if (OutR==1) ENC_RIGHT_PUL ++;
  if (OutR==-1) ENC_RIGHT_PUL --;
}

long readEncoder(int i) 
{
  if (i == LEFT) return ENC_LEFT_PUL;
  else return ENC_RIGHT_PUL;
}

void resetEncoder() 
{
  ENC_LEFT_PUL=0;
  ENC_RIGHT_PUL=0;
  return;
}

void initEnc()
{
  NewL = digitalReadFast(ENC_LEFT_A) * 2 + digitalReadFast(ENC_LEFT_B);
  NewR = digitalReadFast(ENC_RIGHT_A) * 2 + digitalReadFast(ENC_RIGHT_B);
  OldL = NewL;
  OldR = NewR;
}
