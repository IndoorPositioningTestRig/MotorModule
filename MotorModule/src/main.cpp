#include "Arduino.h"

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

int EncoderPinA = 11;
int EncoderPinB = 12;

int EncoderLast = LOW;
int EncoderCurrent = LOW;

int EncoderPos = 0;
int desiredPos = 0;

String Command = "0";

void setup()
{
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
  desiredPos = length;
  Serial.print("Desired length: ");
  Serial.println(desiredPos);
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
  if (desiredPos == EncoderPos)
  {
    Serial.println("Correct position");
    SmState = DONE;
  }
  EncoderLast = EncoderCurrent;
}

void Sm_Done(void)
{
  // transmit done and wait for received
  Command = "";
  Serial.println("Done");
  SmState = LISTENING;
}