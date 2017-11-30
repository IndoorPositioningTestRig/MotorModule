#include "Arduino.h"
#define PI 3.1415926535897932384626433832795
#define ENCODER_DIAMETER 32
#define TICKS 128
#define MMPERTICK (ENCODER_DIAMETER * PI) / TICKS

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
double EncoderPos = 0;
double desiredPos = 0;

int desiredSpeed = 0;
int currentSpeed = 0;

bool direction;
int acceleration = 0;

String Command = "0";

void interruptEncoder();

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

  //interrupt setup:
  attachInterrupt(digitalPinToInterrupt(EncoderPinA), interruptEncoder, RISING);

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

//interrupt functions:
void interruptEncoder()
{
  if (digitalRead(EncoderPinB) == LOW)
    EncoderPos -= MMPERTICK;
  else
    EncoderPos += MMPERTICK;
  Serial.print("Current length: ");
  Serial.print(EncoderPos);
  Serial.print(" Desired length: ");
  Serial.print(desiredPos);
  Serial.print(" Current speed: ");
  Serial.println(currentSpeed);
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
  Serial.println(currentSpeed);
  SmState = DONE;
}
/*
* 
*
*/
void Sm_Moving(void)
{
  // Move rope to desired length
  if (desiredPos > EncoderPos)
    direction = false;
  else
    direction = true;

  // Speed
  if (acceleration > 10)
  {
    // Breakingzone
    if (((EncoderPos > desiredPos - 50 && !direction) || (EncoderPos < desiredPos + 50 && direction)) && currentSpeed > 30)
    {
      currentSpeed--;
    }
    // Accelerate
    else if (currentSpeed < desiredSpeed)
    {
      currentSpeed = desiredSpeed;
      //currentSpeed++;
    }
    acceleration = 0;
  }
  acceleration++;

  if ((EncoderPos < (desiredPos + MMPERTICK)) && (EncoderPos > (desiredPos - MMPERTICK)))
  {
    currentSpeed = 0;
    Serial.println("Correct position");
    Serial.print("Desired position: ");
    Serial.println(desiredPos);
    Serial.print("Current position: ");
    Serial.println(EncoderPos);
    SmState = DONE;
  }
  digitalWrite(retractPin, direction);
  digitalWrite(feedPin, !direction);
  analogWrite(motorDriverPwmPin, currentSpeed);
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