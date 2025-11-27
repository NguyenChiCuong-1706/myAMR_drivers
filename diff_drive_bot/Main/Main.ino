#include "Arduino.h"
#include "Comms_driver.h"  

#define USE_TENSSY
#define BAUDRATE 115200
#define Analog_Resolution 16

#if defined(Analog_Resolution) && Analog_Resolution == 16
  #define PWM_Resolution 65536
  #define PWM_MAX 65000
#else
  #define PWM_Resolution 255
#endif

/*//////////////////////////// Global Variable Declaration ///////////////////////////*/
struct PID{
  double Setpoint;
  long Encoder;                 
  long PrevEnc;  

  int PrevPV;

  int Iterm;
  long output;
};

#define LOOP_RATE 30 //Hz
#define AUTO_STOP_INTERVAL 5000

int Kp = 110;
int Ki = 0;
int Kd = 50;
double Ko = 10; 

struct PID LeftPID;
struct PID RightPID;
const int PID_INTERVAL = 1000 / LOOP_RATE;
unsigned long nextPID = PID_INTERVAL;
long lastMotorCommand = AUTO_STOP_INTERVAL;

int8_t OutL,OutR;
int ctrl_mode = 0;
unsigned char moving = 0; 
int OldL=0, NewL=0, OldR=0, NewR=0;
int RF_leftSPD, RF_rightSPD;
float CMD_leftSPD, CMD_rightSPD;
/*//////////////////////////// Global Variable Declaration ///////////////////////////*/


#ifdef USE_TENSSY // define library names
  #define MOTOR
  #define QUAD_ENC
  #define PID_CTRL
  // #define RADIO_FLYSKY_I6
  #define COMMANDS_H
  // #define TEST
  #define DELAY
#endif
 
#ifdef USE_TENSSY /* Include driver functions */
  #include "Motor_driver.h"
  #include "encoder_driver.h"
  #include "Controller.h"
  #include "Radio_driver.h"
#endif


float eT, currentTime, previousTime;
void waitForSamplingTime(float Ts) //in second
{
  previousTime = currentTime;                   
  currentTime = micros();                      
  eT = (currentTime - previousTime) / 1000000;  
  if (eT < 0) eT = Ts;
  while (eT < Ts) {
    currentTime = micros();                       
    eT = (currentTime - previousTime) / 1000000;  
  }
} 

void setup() 
{
  Serial.begin(BAUDRATE);

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

  analogWriteResolution(Analog_Resolution);
  
  resetEncoder();
  initEnc();
}



void loop()
{
  leftEncoderISR();
  rightEncoderISR();

#ifdef RADIO_FLYSKY_I6
  receive();
  RF_read();
  LeftPID.Setpoint = RF_leftSPD;
  RightPID.Setpoint = RF_rightSPD;
#endif

#ifdef COMMANDS_H
  readCommand();
#endif

#ifdef PID_CTRL
  if (millis() > nextPID) {
    runPID();
    nextPID += PID_INTERVAL;
  }
#endif

#ifdef TEST
  moving =1;
  // LeftPID.Setpoint = 40;
  // RightPID.Setpoint = 40;
  // motor1_ctrl(0);
  // motor2_ctrl(0);

  // Serial.print(millis());   Serial.print(" ");
  Serial.print(LeftPID.PrevPV);    Serial.print(" ");  
  Serial.println(40);
#endif

#ifdef DELAY
  waitForSamplingTime(0.000001);
#endif

}