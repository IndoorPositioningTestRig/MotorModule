#include <SoftwareSerial.h>
#include "main.h"
volatile const int MID = 1;

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

String Command = "";

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
  bool isReceiving = false;
  if (Rs485Serial.available())
  {
    char c = (char)Rs485Serial.read();
    if (c == '*')
      isReceiving = true;

    while (isReceiving)
    {
      if (Rs485Serial.available())
      {
        c = (char)Rs485Serial.read();
        if (c == '#')
          isReceiving = false;
        else
          Command += c;
      }
    }
  }
  if (Command != "")
  {
    int ProtocolId = -1, ModuleId = -1;
    ProtocolId = Command.substring(0, 1).toInt();
    ModuleId = Command.substring(2, 3).toInt();
    
    Serial.print("Received: ");
    Serial.println(Command);
    Serial.print("protocolId: ");
    Serial.println(ProtocolId);
    if (ModuleId == MID || ModuleId == 0)
    {
      switch (ProtocolId)
      {
      case 1:
        Serial.println("Switched to setting length state");
        SmState = SETTING_LENGTH;
        break;
      case 2:
        SmState = MOVING;
        Serial.println("Switched to moving state");
        break;
      case 5:
        int ePos, dPos;
        getEncoderData(ePos, dPos);
        Serial.print("Current length: ");
        Serial.print(ePos);
        Serial.print(" Length in mm: ");
        Serial.print(ePos * ((ENCODER_DIAMETER * PI) / TICKS));
        Serial.print(" Desired length in mm: ");
        Serial.println(dPos * ((ENCODER_DIAMETER * PI) / TICKS));
        Command = "";
        break;
      default:
        Serial.print("Received unknown command");
        Command = "";
        break;
      }
    }
    else
    {
      Serial.print("Received Wrong destination");
      Command = "";
    }
  }
}

void Sm_SettingLength(void)
{
  int Length = Command.substring(Command.indexOf('|', 2) + 1, Command.lastIndexOf('|')).toInt();
  int Speed = Command.substring(Command.lastIndexOf('|') + 1, Command.length()).toInt();

  // Set correct length
  Serial.print("length: ");
  Serial.print(Length);
  Serial.print(" speed: ");
  Serial.println(Speed);
  setEncoderData(Length, Speed);

  int ePos, dPos;
  getEncoderData(ePos, dPos);
  Serial.print("Current length: ");
  Serial.print(ePos);
  Serial.print(" Length in mm: ");
  Serial.print(ePos * ((ENCODER_DIAMETER * PI) / TICKS));
  Serial.print(" Desired length in mm: ");
  Serial.print(dPos * ((ENCODER_DIAMETER * PI) / TICKS));
  Command = "";
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

  int ePos, dPos;
  getEncoderData(ePos, dPos);
  Serial.print("Length: ");
  Serial.print(ePos * ((ENCODER_DIAMETER * PI) / TICKS));
  Serial.print("Desired length: ");
  Serial.println(dPos * ((ENCODER_DIAMETER * PI) / TICKS));

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
  Rs485Serial.write('*');
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
  bool isReceiving = false;
  if (Rs485Serial.available())
  {
    char c = (char)Rs485Serial.read();
    if (c == '*')
      isReceiving = true;

    while (isReceiving)
    {
      if (Rs485Serial.available())
      {
        c = (char)Rs485Serial.read();
        if (c == '#')
          isReceiving = false;
        else
          Command += c;
      }
    }
  }
  if (Command != "")
  {
    int ProtocolId = -1, ModuleId = -1;
    ProtocolId = Command.substring(0, 1).toInt();
    ModuleId = Command.substring(2, 3).toInt();
    if (ProtocolId == 3 && ModuleId == MID)
    {
      SmState = LISTENING;
      Command = "";
    }
    else
    {
      Serial.println("Received ack for different module");
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