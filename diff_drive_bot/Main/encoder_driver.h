#ifdef  QUAD_ENC
  #define ENC_LEFT_A 16  // Motor1
  #define ENC_LEFT_B 15

  #define ENC_RIGHT_A 4 // Motor1
  #define ENC_RIGHT_B 5

  #define PPR 1288 //9337.12 

#endif


void leftEncoderISR();
void rightEncoderISR();
long readEncoder(int i);

void resetEncoder();
void initEnc();
