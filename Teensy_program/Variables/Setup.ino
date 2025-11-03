void setup() 
{
  Serial.begin(115200);

  pinMode(ENC_LEFT_A, INPUT_PULLUP);
  pinMode(ENC_LEFT_B, INPUT_PULLUP);
  
  pinMode(ENC_RIGHT_A, INPUT_PULLUP);
  pinMode(ENC_RIGHT_B, INPUT_PULLUP);

  pinMode(EN_M1, OUTPUT);
  pinMode(EN_M2, OUTPUT);  

  pinMode(PWML1_M1, OUTPUT);
  pinMode(PWML2_M1, OUTPUT);

  pinMode(PWML1_M2, OUTPUT);
  pinMode(PWML2_M2, OUTPUT);

  analogWriteResolution(16);
  
  resetEnc();
  // Initial state of encoder
  NewL = digitalReadFast(ENC_LEFT_A) * 2 + digitalReadFast(ENC_LEFT_B);
  NewR = digitalReadFast(ENC_RIGHT_A) * 2 + digitalReadFast(ENC_RIGHT_B);
  OldL = NewL;
  OldR = NewR;

  attachInterrupt(digitalPinToInterrupt(ENC_LEFT_A), leftEncoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_LEFT_B), leftEncoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_RIGHT_A), rightEncoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_RIGHT_B), rightEncoderISR, CHANGE);
}

