#include <IBusBM.h>

IBusBM ibus;

int receiver_values[6];
void radio_begin()
{
  Serial1.begin(115200);
  ibus.begin(Serial1, IBUSBM_NOTIMER);  // <-- important on Teensy
}

// read iBUS and fill receiver_values[]
void receive()
{
  ibus.loop();   // must be called often

  for (int ch = 0; ch < 6; ch++) {
    uint16_t raw = ibus.readChannel(ch);   // 0..13, but FS-i6 uses 0..5
    if (raw < 1000 || raw > 2000) {
      receiver_values[ch] = 0;
    } else {
      receiver_values[ch] = map(raw, 1000, 2000, -PWM_MAX, PWM_MAX);
    }
  }
}

// mix channels to your robot speeds
void RF_read()
{
  long throttle = receiver_values[1];
  long rot      = receiver_values[0]-50;

  long dead = 50;  
  if (labs(throttle) < dead) throttle = 0;
  if (labs(rot)      < dead) rot      = 0;

  // mode from CH5
  if (receiver_values[4] > 0) {
    ctrl_mode = 1;
  } else {
    ctrl_mode = 0;
  }

  long m1 = 0, m2 = 0;

  if (ctrl_mode == 1) {
    m1 = throttle + rot;
    m2 = throttle - rot;
  } else {
    m1 = 0;
    m2 = 0;
  }

  // clamp to [-PWM_MAX, +PWM_MAX]
  if (m1 >  PWM_MAX) m1 =  PWM_MAX;
  if (m1 < -PWM_MAX) m1 = -PWM_MAX;
  if (m2 >  PWM_MAX) m2 =  PWM_MAX;
  if (m2 < -PWM_MAX) m2 = -PWM_MAX;

  RF_leftSPD  = (int)m1;
  RF_rightSPD = (int)m2;

}

