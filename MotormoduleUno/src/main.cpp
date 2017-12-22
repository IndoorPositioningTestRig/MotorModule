#include <SoftwareSerial.h>
#include "main.h"
volatile const int MID = 2;

/*
* State machine declaration
*/
typedef enum {
  LISTENING,
  SETTING_LENGTH,
  MOVING,
  DONE,
  WAIT_FOR_ACK
} StateType;

typedef struct
{
  StateType State;
  void (*func)(void);
} StateMachineType;

void Sm_Listening(void);
void Sm_Done(void);
void Sm_SettingLength(void);
void Sm_Moving(void);
void Sm_WaitForAck(void);

StateMachineType StateMachine[] = {
    {LISTENING, Sm_Listening},
    {SETTING_LENGTH, Sm_SettingLength},
    {MOVING, Sm_Moving},
    {DONE, Sm_Done},
    {WAIT_FOR_ACK, Sm_WaitForAck}};

StateType SmState = LISTENING;

String Command = "0";

SoftwareSerial Rs485Serial(6, 5);

void setup()
{
  setupMotor();
  setupEncoder();
  setupSwitches();

  Rs485Serial.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  if (isSwitchPressed())
  {
    //ONE endswitch is pressed!
    //TODO: handle this problem
  }

  if (SmState < 5)
  {
    (*StateMachine[SmState].func)();
  }
  else
  {
  }
}

//state functions:
void Sm_Listening(void)
{
  while (Rs485Serial.available())
  {
    Command += (char)Rs485Serial.read();
    delay(1);
  }
  if (Command != "")
  {
    Serial.print("Received command:");
    Serial.println(Command);
    int ProtocolId = Command.substring(0, 1).toInt();
    int ModuleId = Command.substring(2, 3).toInt();
    switch (ProtocolId)
    {
    case 1:
      if (ModuleId == MID)
      {
        SmState = SETTING_LENGTH;
        Serial.println("Switched to setting length state");
      }
      else
      {
        Command = "";
        Serial.println("Received command for wrong module");
      }
      break;
    case 2:
      SmState = MOVING;
      Serial.println("Switched to moving state");
      break;
    case 3:
      resetEncoderData();
      Command = "";
      break;
    case 4:
      int ePos, dPos;
      getEncoderData(ePos, dPos);
      Serial.print("Current length: ");
      Serial.print(ePos);
      Serial.print(" Length in mm: ");
      Serial.print(ePos * ((ENCODER_DIAMETER * PI) / TICKS));
      Serial.print(" Ticks: ");
      Serial.println(dPos);
      Command = "";
      break;
    case 5:
      addEncoderPos();
      break;
    default:
      Serial.print("Received unknown command: ");
      Serial.println(Command);
      Command = "";
      break;
    }
  }
}

void Sm_SettingLength(void)
{
  // Set correct length
  int length = Command.substring(Command.indexOf('|', 3) + 1, Command.indexOf('|', 4)).toInt();
  int speed = Command.substring(Command.indexOf('|', 4) + 1, Command.length()).toInt();
  Serial.print("length: ");
  Serial.print(length);
  Serial.print(" speed: ");
  Serial.println(speed);
  setEncoderData(length, speed);
  SmState = DONE;
}

/*
* 
*/
void Sm_Moving(void)
{
  bool retractDirection, done;
  int newSpeed;
  getPwmSpeed(newSpeed);
  calculateMotorSpeed(retractDirection, newSpeed, done);
  Serial.print("main got speed: ");
  Serial.println(newSpeed);

  if (done)
  {
    SmState = DONE;
  }
  setMotor(retractDirection, newSpeed);
}

/*
* In this state the application should transmit a done signal.
* The application will then wait for the main controller to respond.
* When the acknowledge is received the state will go to listening.
*/
void Sm_Done(void)
{
  // transmit done
  
  Command = "";
  Serial.println("Done");
  Rs485Serial.write('4');
  Rs485Serial.write('|');
  char mid = '0' + MID;
  Rs485Serial.write(mid);
  Rs485Serial.write('#');
  // wait 1 second for receive
  SmState = WAIT_FOR_ACK;
  Serial.println("Waiting for acknowledge");
  // after 1 second transmit again
}

int timer = 0;
void Sm_WaitForAck(void)
{
  if (Rs485Serial.available())
  {
    while (Rs485Serial.available())
    {
      Command += (char)Rs485Serial.read();
    }
    int ProtocolId = Command.substring(0, 1).toInt();
    int MidId = Command.substring(2, 3).toInt();
    if (ProtocolId == 3 && MidId == MID)
    {
      SmState = LISTENING;
      Command = "";
    }
  }

  timer++;
  if (timer > 10000)
  {
    timer = 0;
    SmState = DONE;
  }
}