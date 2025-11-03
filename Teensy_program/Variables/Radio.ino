int channel_count = 0;
int mode = 0;
int pwm_range=PWM_Resolution;
boolean prt = false;
int res_min = 950, res_max = 2020;
int receiver_values[] = {0, 0, 0, 0, 0, 0};
int receiver_pins[] = {A0, A1, A2, A3, A4, A5};

void receive() {
  receiver_values[channel_count] = map(pulseIn (receiver_pins[channel_count], HIGH), res_min, res_max, -pwm_range, pwm_range);
  channel_count++;
  if (channel_count == 6){
    channel_count = 0;
  }
  boolean activevalues = true;
  for (int i = 0; i < 6; i++) {
    if (prt) {
      Serial.print("CH"); Serial.print(i); Serial.print(" : ");
      Serial.print(receiver_values[i]); Serial.print(",\t");
    }
    if (receiver_values[i] < -500) {
      activevalues = false;
    }
  }
  mode = 0;
  if (!activevalues) {
    mode = -1;
  } else if (receiver_values[4] > -100) {
    mode = 2;
  } else if (receiver_values[5] > -100) {
    mode = 1;
  }
  if (prt) {
    Serial.println("");
  }
}

void RF_read(int *des_m1, int *des_m2)
{
  int m1 = 0;
  int m2 = 0;
  int rot = receiver_values[0];

  if (mode == 1) {
    m1 = receiver_values[1] / 2 + (rot)/1.5;
    m2 = receiver_values[1] / 2 - (rot)/1.5;

  } else if (mode == 2) {
    m1 = receiver_values[1] + rot / 1.75;
    m2 = receiver_values[1] - rot / 1.75;
  }
  *des_m1=m1;
  *des_m2=m2;
}