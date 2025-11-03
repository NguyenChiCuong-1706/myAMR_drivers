#define ENC_LEFT_A 2
#define ENC_LEFT_B 3
#define ENC_RIGHT_A 4
#define ENC_RIGHT_B 5

#define EN_M1 10
#define PWML1_M1 11
#define PWML2_M1 12
#define EN_M2 13
#define PWML1_M2 14
#define PWML2_M2 15

#define Ts 10000 //micros
#define PPR 9337.12 
#define MAX_SPD 100 //rpm

#define Kp 1
#define Ki 1
#define Kd 1
#define PIDrate 10 //ms
#define PWM_Resolution 65536

long Pre_LEFT_PUL;
long Pre_RIGHT_PUL;
volatile long ENC_LEFT_PUL=0;
volatile long ENC_RIGHT_PUL=0;

unsigned long lastTime=0;
volatile int8_t OutL,OutR;
volatile int8_t OldL=0, NewL=0, OldR=0, NewR=0;

const int8_t QEM [16] = {0,-1,1,2,1,0,2,-1,-1,2,0,1,2,1,-1,0};

struct PID{
  inline static unsigned long prevT=0;
  inline static float output;
  inline static float pre_er;
  inline static float preIterm;
};