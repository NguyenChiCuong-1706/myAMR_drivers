
int arg = 0;                // A pair of varibles to help parse serial commands
int idex = 0;
char chr;                   // Variable to hold an input character
char cmd;                   // Variable to hold the current single-character command
long arg1, arg2;            // The arguments converted to integers
char argv1[16], argv2[16];  // Character arrays to hold the first and second arguments


void resetCommand() {
  cmd = '\0';
  memset(argv1, 0, sizeof(argv1));
  memset(argv2, 0, sizeof(argv2));
  arg1 = 0; arg2 = 0; arg = 0;
  idex = 0;
}

void runCommand() {
  int i = 0;
  char *p = argv1;
  char *str;
  int pid_args[4];
  arg1 = atoi(argv1);
  arg2 = atoi(argv2);
  
  switch(cmd) {

  case GET_BAUDRATE:
    Serial.println(BAUDRATE);
    break;

  case ANALOG_READ:
    Serial.println(analogRead(arg1));
    break;

  case DIGITAL_READ:
    Serial.println(digitalRead(arg1));
    break;

  case ANALOG_WRITE:
    analogWrite(arg1, arg2);
    Serial.println("OK"); 
    break;

  case DIGITAL_WRITE:
    if (arg2 == 0) digitalWrite(arg1, LOW);
    else if (arg2 == 1) digitalWrite(arg1, HIGH);
    Serial.println("OK"); 
    break;

  case PIN_MODE:
    if (arg2 == 0) pinMode(arg1, INPUT);
    else if (arg2 == 1) pinMode(arg1, OUTPUT);
    Serial.println("OK");
    break;

  case PING:
    Serial.println("Ping");
    break;
    
  #ifdef USE_TENSSY
  case READ_ENCODERS:
    Serial.print(readEncoder(LEFT));
    Serial.print(" ");
    Serial.println(readEncoder(RIGHT));
    break;

  case RESET_ENCODERS:
    resetEncoder();
    resetPID();
    Serial.println("OK");
    break;

  case MOTOR_SPEEDS:
    lastMotorCommand = millis();
    if (arg1 == 0 && arg2 == 0) {
      motor1_ctrl(0);
      motor2_ctrl(0);
      resetPID();
      moving = 0;
    }
    else moving = 1;
    LeftPID.Setpoint = arg1;
    RightPID.Setpoint = arg2;
    Serial.println("OK"); 
    break;

  case MOTOR_RAW_PWM:
    lastMotorCommand = millis();
    resetPID();
    moving = 0; // disable the PID
    motor1_ctrl(arg1);
    motor2_ctrl(arg2);
    Serial.print(arg1);  Serial.print(" "); Serial.println(arg2); 
    Serial.println("OK"); 
    break;

  case UPDATE_PID:
    while ((str = strtok_r(p, ":", &p)) != NULL) {
       pid_args[i] = atoi(str);
       i++;
    }
    Kp = pid_args[0];
    Kd = pid_args[1];
    Ki = pid_args[2];
    Ko = pid_args[3];
    Serial.println("OK");
    break;
  #endif

  default:
    Serial.println("Invalid Command");
    break;
  }
}

void readCommand()
{
   while (Serial.available() > 0) {
    
    chr = Serial.read();      // Read the next character

    // Terminate a command with a CR
    if (chr == 13) {
      if (arg == 1) argv1[idex] = '\0';
      else if (arg == 2) argv2[idex] = '\0';
      runCommand();
      resetCommand();
    }
    // Use spaces to delimit parts of the command
    else if (chr == ' ') {
      // Step through the arguments
      if (arg == 0) arg = 1;
      else if (arg == 1)  {
        argv1[idex] = '\0';
        arg = 2;
        idex = 0;
      }
      continue;
    }
    else {
      if (arg == 0) {
        // The first arg is the single-letter command
        cmd = chr;
      }
      else if (arg == 1) {
        // Subsequent arguments can be more than one character
        argv1[idex] = chr;
        idex++;
      }
      else if (arg == 2) {
        argv2[idex] = chr;
        idex++;
      }
    }
  }
  
  #ifdef COMMANDS_H // run a PID calculation for control commands
    if ((millis() - lastMotorCommand) > AUTO_STOP_INTERVAL) {;      // the auto-stop interval for command
      motor1_ctrl(0);
      motor2_ctrl(0);
      moving = 0;
      resetPID();
    }
  #endif
}