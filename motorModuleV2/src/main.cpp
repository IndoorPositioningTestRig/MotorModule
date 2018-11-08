#include <Arduino.h>
#include "MotorLogic/Logic.hpp"
#include "Communication.hpp"

static MotorLogic::Logic *logic;
static Communication *communication;

void setup()
{
  Serial.begin(9600);
    while (!Serial);
#ifdef WAIT_SERIAL
  while (!Serial)
    ;
#endif
  Serial.println("starting...");
  logic = new MotorLogic::Logic();

  // communication = new Communication();
  Serial1.begin(9600);

  pinMode(10, INPUT);
  digitalWrite(10, 0);
  pinMode(11, INPUT);
  digitalWrite(11, 0);

  //pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW); //LOW is write, HIGH is read
}

void loop()
{
 logic->loop();
}
