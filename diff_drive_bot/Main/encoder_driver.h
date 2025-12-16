#ifdef  QUAD_ENC
  #define ENC_LEFT_A 34  // Motor1
  #define ENC_LEFT_B 35

  #define ENC_RIGHT_A 36 // Motor1
  #define ENC_RIGHT_B 37

  #define PPR 9944    //  4x.resolution=44, ratio=226
  #define max_rpm 15  //  RPS = RPM/60 = 0.25 -> PPS = 0.25*PPR = 2486
                      //  max_PPL = 2,486 × (1/30) ≈ 82.9
#endif


void leftEncoderISR();
void rightEncoderISR();
long readEncoder(int i);

void resetEncoder();
void initEnc();
