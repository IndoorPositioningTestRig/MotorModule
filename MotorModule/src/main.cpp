#include "Arduino.h"
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
// Motor driver
int retractPin = 2;
int motorDriverPwmPin = 3;
int feedPin = 4;

// End switches
int switchAPin = 5;
int switchBPin = 6;
// Encoder
int EncoderPinA = 7;
int EncoderPinB = 8;

// Global variables
int EncoderLast = LOW;
int EncoderCurrent = LOW;

int EncoderPos = 0;
int desiredPos = 0;

int desiredSpeed = 0;
int currentSpeed = 0;

int acceleration = 0;

String Command = "0";

void setup()
{
  // Motor driver setup
  pinMode(retractPin, OUTPUT);
  pinMode(motorDriverPwmPin, OUTPUT);
  pinMode(feedPin, OUTPUT);

  // TODO Switch setup

  // encoder setup
  pinMode(EncoderPinA, INPUT);
  pinMode(EncoderPinB, INPUT);
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
  desiredPos = length;
  desiredSpeed = speed;
  Serial.print("Current length: ");
  Serial.print(EncoderPos);
  Serial.print(" Desired length: ");
  Serial.print(desiredPos);
  Serial.print(" Speed: ");
  Serial.println(desiredSpeed);

  SmState = DONE;
}

void Sm_Moving(void)
{
  // Move rope to desired length
  EncoderCurrent = digitalRead(EncoderPinA);
  if ((EncoderLast == LOW) && (EncoderCurrent == HIGH))
  {
    if (digitalRead(EncoderPinB) == LOW)
    {
      EncoderPos--;
    }
    else
    {
      EncoderPos++;
    }
    Serial.print("Current length: ");
    Serial.print(EncoderPos);
    Serial.print(" Desired length: ");
    Serial.println(desiredPos);
  }
  EncoderLast = EncoderCurrent;

  if (currentSpeed < desiredSpeed && acceleration > 500)
  {
    currentSpeed++;
    acceleration = 0;
  }
  else
  {
    acceleration++;
  }
  if (desiredPos > EncoderPos)
  {
    digitalWrite(retractPin, false);
    digitalWrite(feedPin, true);
    analogWrite(motorDriverPwmPin, currentSpeed);
  }
  else if (desiredPos < EncoderPos)
  {
    digitalWrite(retractPin, true);
    digitalWrite(feedPin, false);
    analogWrite(motorDriverPwmPin, currentSpeed);
  }
  else
  {
    currentSpeed = 0;
    analogWrite(motorDriverPwmPin, currentSpeed);
    Serial.println("Correct position");
    SmState = DONE;
  }
}

void Sm_Done(void)
{
  // transmit done and wait for received
  Command = "";
  Serial.println("Done");
  SmState = LISTENING;
}