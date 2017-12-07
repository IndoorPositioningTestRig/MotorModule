#include "main.h"


/*
* State machine declaration
*/
typedef enum {
  LISTENING,
  SETTING_LENGTH,
  MOVING,
  DONE
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

StateMachineType StateMachine[] = {
    {LISTENING, Sm_Listening},
    {SETTING_LENGTH, Sm_SettingLength},
    {MOVING, Sm_Moving},
    {DONE, Sm_Done}};

StateType SmState = LISTENING;

/*
* GPIO declaration
*/

// End switches
int switchAPin = 5;
int switchBPin = 6;

String Command = "0";


void setup()
{
  setupMotor();
  setupEncoder();
  // TODO Switch setup

  Serial.begin(9600);
}

void loop()
{
  if (SmState < 4)
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
  while (Serial.available())
  {
    Command += (char)Serial.read();
  }
  if (Command != "")
  {
    int ProtocolId = Command.substring(0, 1).toInt();
    switch (ProtocolId)
    {
    case 1:
      SmState = SETTING_LENGTH;
      Serial.println("Switched to setting length state");
      break;
    case 2:
      SmState = MOVING;
      Serial.println("Switched to moving state");
      break;
    case 3:
      EncoderPos = 0;
      desiredPos = 0;
      Command = "";
      break;
    case 4:
      Serial.print("Current length: ");
      Serial.print(EncoderPos);
      Serial.print(" Length in mm: ");
      Serial.print(EncoderPos * ((ENCODER_DIAMETER * PI) / TICKS));
      Serial.print(" Ticks: ");
      Serial.println(desiredPos);
      Command = "";
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
  calculateMotorSpeed(retractDirection,newSpeed,done);
  if (done)
  {
      currentSpeed = 0;
      Serial.print("Current length: ");
      Serial.print(EncoderPos);
      Serial.print(" Desired length: ");
      Serial.print(desiredPos);
      Serial.print(" Current speed: ");
      Serial.println(currentSpeed);
      SmState = DONE;
  }
  setMotor(direction,currentSpeed);
}

/*
* In this state the application should transmit a done signal.
* The application will then wait for the main controller to respond.
* When the acknowledge is received the state will go to listening.
*/
void Sm_Done(void)
{
  // transmit done and wait for received
  Command = "";
  Serial.println("Done");
  SmState = LISTENING;
}